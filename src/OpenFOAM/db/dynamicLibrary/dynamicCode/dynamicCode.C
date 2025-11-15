/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2025 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "dynamicCode.H"
#include "dynamicCodeContext.H"
#include "stringOps.H"
#include "IFstream.H"
#include "OFstream.H"
#include "OSspecific.H"
#include "etcFiles.H"
#include "dictionary.H"

#include "parse_wmake.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

int Foam::dynamicCode::allowSystemOperations
(
    Foam::debug::infoSwitch("allowSystemOperations", 0)
);


const Foam::word Foam::dynamicCode::codeTemplateEnvName
    = "FOAM_CODE_TEMPLATES";

const Foam::fileName Foam::dynamicCode::codeTemplateDirName
    = "codeTemplates/dynamicCode";
#ifndef WM_OPTIONS
#error "WM_OPTIONS must be defined as macro, in compile command"
#else
const char* const wm_options_string = STR(WM_OPTIONS);
#endif
//const char* const Foam::dynamicCode::libTargetRoot =
//    "LIB = $(PWD)/../platforms/$(WM_OPTIONS)/lib/lib";

const char* const Foam::dynamicCode::topDirName = "dynamicCode";


// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

void Foam::dynamicCode::checkSecurity
(
    const char* title,
    const dictionary& dict
)
{
    if (isAdministrator())
    {
        FatalIOErrorInFunction(dict)
            << "This code should not be executed by someone with administrator"
            << " rights due to security reasons." << nl
            << "(it writes a shared library which then gets loaded "
            << "using dlopen)"
            << exit(FatalIOError);
    }

    if (!allowSystemOperations)
    {
        FatalIOErrorInFunction(dict)
            << "Loading a shared library using case-supplied code is not"
            << " enabled by default" << nl
            << "because of security issues. If you trust the code you can"
            << " enable this" << nl
            << "facility be adding to the InfoSwitches setting in the system"
            << " controlDict:" << nl << nl
            << "    allowSystemOperations 1" << nl << nl
            << "The system controlDict is either" << nl << nl
            << "    ~/.OpenFOAM/$WM_PROJECT_VERSION/controlDict" << nl << nl
            << "or" << nl << nl
            << "    $WM_PROJECT_DIR/etc/controlDict" << nl
            << endl
            << exit(FatalIOError);
    }
}


Foam::word Foam::dynamicCode::libraryBaseName(const fileName& libPath)
{
    word libName(libPath.name(true));
    libName.erase(0, 3);    // Remove leading 'lib' from name
    return libName;
}



// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void Foam::dynamicCode::copyAndFilter
(
    ISstream& is,
    OSstream& os,
    const HashTable<string>& mapping
)
{
    if (!is.good())
    {
        FatalErrorInFunction
            << "Failed opening for reading " << is.name()
            << exit(FatalError);
    }

    if (!os.good())
    {
        FatalErrorInFunction
            << "Failed writing " << os.name()
            << exit(FatalError);
    }

    // Copy file while rewriting $VARS and ${VARS}
    string line;
    do
    {
        // Read the next line without continuation
        is.getLine(line, false);

        // Expand according to mapping.
        // Expanding according to env variables might cause too many
        // surprises
        stringOps::inplaceExpandCodeTemplate(line, mapping);
        os.writeQuoted(line, false) << nl;
    }
    while (is.good());
}


Foam::fileName Foam::dynamicCode::resolveTemplate
(
    const fileName& templateName
)
{
    // Try to get template from FOAM_CODESTREAM_TEMPLATES
    const fileName templateDir(Foam::getEnv(codeTemplateEnvName));

    fileName file;
    if (!templateDir.empty() && isDir(templateDir))
    {
        file = templateDir/templateName;
        if (!isFile(file, false, true))
        {
            file.clear();
        }
    }

    // Not found - fallback to ~OpenFOAM expansion
    if (file.empty())
    {
        file = findEtcFile(codeTemplateDirName/templateName);
    }

    return file;
}


bool Foam::dynamicCode::resolveTemplates
(
    const UList<fileName>& templateNames,
    DynamicList<fileName>& resolvedFiles,
    DynamicList<fileName>& badFiles
)
{
    // Try to get template from FOAM_CODESTREAM_TEMPLATES
    const fileName templateDir(Foam::getEnv(codeTemplateEnvName));

    bool allOkay = true;
    forAll(templateNames, fileI)
    {
        const fileName& templateName = templateNames[fileI];

        fileName file;
        if (!templateDir.empty() && isDir(templateDir))
        {
            file = templateDir/templateName;
            if (!isFile(file, false, true))
            {
                file.clear();
            }
        }

        // Not found - fallback to ~OpenFOAM expansion
        if (file.empty())
        {
            file = findEtcFile(codeTemplateDirName/templateName);
        }

        if (file.empty())
        {
            badFiles.append(templateName);
            allOkay = false;
        }
        else
        {
            resolvedFiles.append(file);
        }
    }

    return allOkay;
}


bool Foam::dynamicCode::writeCommentSHA1(Ostream& os) const
{
    const bool hasSHA1 = filterVars_.found("SHA1sum");

    if (hasSHA1)
    {
        os  << "# dynamicCode:\n# SHA1 = ";
        os.writeQuoted(filterVars_["SHA1sum"], false) << "\n\n";
    }

    return hasSHA1;
}


bool Foam::dynamicCode::createMakeFiles() const
{
    // Create Make/files
    if (compileFiles_.empty())
    {
        return false;
    }

    const fileName dstFile(this->codePath()/"CMakeLists.txt");

    // Create dir
    mkDir(dstFile.path());

    OFstream os(dstFile);
    // Info<< "Writing to " << dstFile << endl;
    if (!os.good())
    {
        FatalErrorInFunction
                << "Failed writing " << dstFile
                << exit(FatalError);
    }

    writeCommentSHA1(os);

    os<<"cmake_minimum_required(VERSION 3.28)"<<nl;

    os<<"project("<<codeName_.c_str()<<" LANGUAGES CXX)"<<nl;

    os<<"set(target_name "<<codeName_.c_str()<<")"<<nl;
    //$(PWD)/../platforms/$(WM_OPTIONS)/lib/lib";
    os<<"set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../platforms/"<<wm_options_string<<"/lib)"<<nl;

    os<<"add_library(${target_name} SHARED "<<nl;
    // Write compile files
    forAll(compileFiles_, fileI)
    {
        os<<"    ";
        os.writeQuoted(compileFiles_[fileI].name(), false) << nl;
    }

    os<<")"<<nl;

    os<<"include(options.cmake)"<<nl;

    return true;
}


bool Foam::dynamicCode::createMakeOptions() const
{
    // Create Make/options
    if (compileFiles_.empty() || makeOptions_.empty())
    {
        return false;
    }

    const fileName dstFile(this->codePath()/"options.cmake");

    // Create dir
    mkDir(dstFile.path());
    OFstream os(dstFile);
    // Info<< "Writing to " << dstFile << endl;
    if (!os.good())
    {
        FatalErrorInFunction
                << "Failed writing " << dstFile
                << exit(FatalError);
    }

    writeCommentSHA1(os);

    auto vars = wmakeParse::get_environment_variables();

    wmakeParse::wmake_parse_option option{};
    option.when_undefined_reference=wmakeParse::undefined_reference_behavior::throw_exception;
    wmakeParse::parse_wmake_file(makeOptions_,vars,option);

    os<<"# Original value of makeOptions: \n# ";
    for(char ch:makeOptions_) {
      os<<ch;
      if(ch=='\n') {
        os<<"# ";
      }
    }
    os<<nl<<nl;

    os<<"find_package(Mikeno CONFIG REQUIRED)"<<nl;

    {
        os<<"target_compile_options(${target_name} PRIVATE"<<nl;
        auto it= vars.find("EXE_INC");
        if(it not_eq vars.end()) {
            os<<"    "<<it->second.c_str()<<nl;
        }
        os<<")"<<nl;
    }

    {
        os<<"target_link_libraries(${target_name} PRIVATE"<<nl;
        os<<"\n"
            "    Mikeno::OpenFOAM_Defines\n"
            "    Mikeno::OpenFOAM\n"
            "    Mikeno::OSspecific\n\n";

        auto it=vars.find("LIB_LIBS");
        if(it not_eq vars.end()) {
            os<<"    "<<it->second.c_str()<<nl;
        }
        os<<")"<<nl;
    }

    return true;
}


bool Foam::dynamicCode::writeDigest(const SHA1Digest& sha1) const
{
    const fileName file = digestFile();
    mkDir(file.path());

    OFstream os(file);
    sha1.write(os, true) << nl;

    return os.good();
}


bool Foam::dynamicCode::writeDigest(const std::string& sha1) const
{
    const fileName file = digestFile();
    mkDir(file.path());

    OFstream os(file);
    os  << '_';
    os.writeQuoted(sha1, false) << nl;

    return os.good();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::dynamicCode::dynamicCode(const word& codeName, const word& codeDirName)
:
    codeRoot_(stringOps::expandEnvVar("$FOAM_CASE")/topDirName),
    libSubDir_(stringOps::expandEnvVar("platforms/$WM_OPTIONS/lib")),
    codeName_(codeName),
    codeDirName_(codeDirName)
{
    if (codeDirName_.empty())
    {
        codeDirName_ = codeName_;
    }

    clear();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

Foam::fileName Foam::dynamicCode::codeRelPath() const
{
    return topDirName/codeDirName_;
}


Foam::fileName Foam::dynamicCode::libRelPath() const
{
    return codeRelPath()/libSubDir_/"lib" + codeName_ + ".so";
}


void Foam::dynamicCode::clear()
{
    compileFiles_.clear();
    copyFiles_.clear();
    createFiles_.clear();
    filterVars_.clear();
    filterVars_.set("typeName", codeName_);
    filterVars_.set("SHA1sum", SHA1Digest().str());

    // Provide default Make/options
    makeOptions_ =
        "EXE_INC = -g\n"
        "\n\nLIB_LIBS = ";
}


void Foam::dynamicCode::reset
(
    const dynamicCodeContext& context
)
{
    clear();

    forAllConstIter(HashTable<string>, context.code(), iter)
    {
        setFilterVariable(iter.key(), iter());
    }

    setFilterVariable("SHA1sum", context.sha1().str());
}


void Foam::dynamicCode::addCompileFile(const fileName& name)
{
    compileFiles_.append(name);
}


void Foam::dynamicCode::addCopyFile(const fileName& name)
{
    copyFiles_.append(name);
}


void Foam::dynamicCode::addCreateFile
(
    const fileName& name,
    const string& contents
)
{
    createFiles_.append(fileAndContent(name, contents));
}


void Foam::dynamicCode::setFilterVariable
(
    const word& key,
    const std::string& value
)
{
    filterVars_.set(key, value);
}


void Foam::dynamicCode::setMakeOptions(const std::string& content)
{
    makeOptions_ = content;
}


bool Foam::dynamicCode::copyOrCreateFiles(const bool verbose) const
{
    if (verbose)
    {
        Info<< "Creating new library in " << this->libRelPath() << endl;
    }

    const label nFiles = compileFiles_.size() + copyFiles_.size();

    DynamicList<fileName> resolvedFiles(nFiles);
    DynamicList<fileName> badFiles(nFiles);

    // Resolve template, or add to bad-files
    resolveTemplates(compileFiles_, resolvedFiles, badFiles);
    resolveTemplates(copyFiles_, resolvedFiles, badFiles);

    if (!badFiles.empty())
    {
        FatalErrorInFunction
            << "Could not find the code template(s): "
            << badFiles << nl
            << "Under the $" << codeTemplateEnvName
            << " directory or via via the ~OpenFOAM/"
            << codeTemplateDirName << " expansion"
            << exit(FatalError);
    }



    // Create dir
    const fileName outputDir = this->codePath();

    // Create dir
    mkDir(outputDir);

    // Copy/filter files
    forAll(resolvedFiles, fileI)
    {
        const fileName& srcFile = resolvedFiles[fileI];
        const fileName dstFile(outputDir/srcFile.name());

        Info << srcFile << " " << dstFile << endl;

        IFstream is(srcFile);
        // Info<< "Reading from " << is.name() << endl;
        if (!is.good())
        {
            FatalErrorInFunction
                << "Failed opening " << srcFile
                << exit(FatalError);
        }

        OFstream os(dstFile);
        // Info<< "Writing to " << dstFile.name() << endl;
        if (!os.good())
        {
            FatalErrorInFunction
                << "Failed writing " << dstFile
                << exit(FatalError);
        }

        // Copy lines while expanding variables
        copyAndFilter(is, os, filterVars_);
    }


    // Create files:
    forAll(createFiles_, fileI)
    {
        const fileName dstFile
        (
            outputDir/stringOps::expandEnvVar(createFiles_[fileI].first())
        );

        mkDir(dstFile.path());
        OFstream os(dstFile);
        // Info<< "Writing to " << createFiles_[fileI].first() << endl;
        if (!os.good())
        {
            FatalErrorInFunction
                << "Failed writing " << dstFile
                << exit(FatalError);
        }
        os.writeQuoted(createFiles_[fileI].second(), false) << nl;
    }


    // Create Make/files + Make/options
    createMakeFiles();
    createMakeOptions();

    writeDigest(filterVars_["SHA1sum"]);

    return true;
}


bool Foam::dynamicCode::wmakeLibso() const
{
    Foam::string configCmd("cmake");
    configCmd+=" -S"+this->codePath();
    configCmd+=" -B"+this->codePath()/"Make";
    configCmd+=" -DCMAKE_C_COMPILER=$WM_CC";
    configCmd+=" -DCMAKE_CXX_COMPILER=$WM_CXX";
    configCmd+=" -DCMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE";
    configCmd+=" -DCMAKE_PREFIX_PATH=$MIKENO_BINARY_INSTALL_PREFIX";
    configCmd+=" --no-warn-unused-cli";
#ifndef FULLDEBUG
    configCmd+=" --log-level=ERROR";
#endif
    Info<< "Invoking " << configCmd << endl;
    if (Foam::system(configCmd)) {
        return false;
    }

    Foam::string buildCmd("cmake");
    buildCmd+=" --build "+this->codePath()/"Make";
#ifndef FULLDEBUG
    buildCmd+=" --log-level=ERROR";
#endif

    Info<<"Invoking "<<buildCmd<<endl;
    if(Foam::system(buildCmd)) {
        return false;
    }

    return true;
}


bool Foam::dynamicCode::upToDate(const SHA1Digest& sha1) const
{
    const fileName file = digestFile();

    if (!exists(file, false, true) || SHA1Digest(IFstream(file)()) != sha1)
    {
        return false;
    }

    return true;
}


bool Foam::dynamicCode::upToDate(const dynamicCodeContext& context) const
{
    return upToDate(context.sha1());
}


// ************************************************************************* //

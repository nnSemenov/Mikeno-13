//
// Created by joseph on 2025/11/15.
//
#include "parse_wmake.H"
#include <exception>
#include <iostream>
#include <print>

extern const char* const test_string;

int main() {

  {
    const char* raw=" \t\r\n\f\v  aaa ibj a = 3   \t \r \n \f \v  ";

    std::println("Trimed: \"{}\"",Foam::wmakeParse::trim(raw));
  }

  std::map<std::string,std::string> dict;
  std::vector<std::string> files;
  try {
    files = Foam::wmakeParse::parse_wmake_file(test_string,dict);
  }catch (const std::exception&e) {
    std::println(std::cerr,"Failed: {}",e.what());
//    std::cerr<<"Failed: "<<e.what()<<std::endl;
    return 1;
  }

  std::println("Success, {} files and {} variables:",files.size(),dict.size());
  for(const auto & file: files) {
    std::println("\"{}\"",file);
  }
  std::println("Vars: ");
//  std::cout<<"Success: \n";
  for(const auto&[key,value]:dict) {
    std::println(R"("{}" = "{}")",key,value);
  }
  std::cout<<std::endl;
  return 0;
}

const char* const test_string="triSurfaceTools                       = triSurface/triSurfaceTools\n"
                              "geometricSurfacePatch                 = triSurface/geometricSurfacePatch\n"
                              "\n"
                              "meshTriangulation/meshTriangulation.C\n"
                              "\n"
                              "triSurface/triSurface.C\n"
                              "triSurface/triSurfaceAddressing.C\n"
                              "triSurface/stitchTriangles.C\n"
                              "\n"
                              "interfaces = triSurface/interfaces\n"
                              "$(interfaces)/STL/writeSTL.C\n"
                              "$(interfaces)/STL/readSTL.C\n"
                              "$(interfaces)/STL/readSTLASCII.L\n"
                              "$(interfaces)/STL/readSTLBINARY.C\n"
                              "$(interfaces)/GTS/writeGTS.C\n"
                              "$(interfaces)/GTS/readGTS.C\n"
                              "$(interfaces)/OBJ/readOBJ.C\n"
                              "$(interfaces)/OBJ/writeOBJ.C\n"
                              "$(interfaces)/SMESH/writeSMESH.C\n"
                              "$(interfaces)/OFF/readOFF.C\n"
                              "$(interfaces)/OFF/writeOFF.C\n"
                              "$(interfaces)/TRI/writeTRI.C\n"
                              "$(interfaces)/TRI/readTRI.C\n"
                              "$(interfaces)/AC3D/readAC.C\n"
                              "$(interfaces)/AC3D/writeAC.C\n"
                              "$(interfaces)/VTK/readVTK.C\n"
                              "$(interfaces)/VTK/writeVTK.C\n"
                              "$(interfaces)/NAS/readNAS.C\n"
                              "\n"
                              "triSurface/geometricSurfacePatch/geometricSurfacePatch.C\n"
                              "triSurface/surfacePatch/surfacePatch.C\n"
                              "triSurface/surfacePatch/surfacePatchIOList.C\n"
                              "\n"
                              "tools/labelledTri/sortLabelledTri.C\n"
                              "\n"
                              "triSurfaceFields/triSurfaceFields.C\n"
                              "\n"
                              "LIB = $(FOAM_LIBBIN)/libtriSurface"
                              "\n"
                              "EXE_INC = \\\n"
                              "    -I$(LIB_SRC)/fileFormats/lnInclude \\\n"
                              "    -I$(LIB_SRC)/surfMesh/lnInclude\n"
                              "\n"
                              "LIB_LIBS = \\\n"
                              "    -lfileFormats \\\n"
                              "    -lsurfMesh";
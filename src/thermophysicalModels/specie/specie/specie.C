/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2023 OpenFOAM Foundation
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

#include "specie.H"

/* * * * * * * * * * * * * * * public constants  * * * * * * * * * * * * * * */

namespace Foam
{
    defineTypeNameAndDebug(specie, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::specie::specie(const word& name, const dictionary& dict)
:
    name_(name),
    Y_(dict.subDict("specie").lookupOrDefault("massFraction", 1.0)),
    molWeight_(dict.subDict("specie").lookup<scalar>("molWeight")),
    // Non-physical default value will force user input them when actually required
    Tc_(dict.subDict("specie").lookupOrDefault("Tc", -1.0)),
    Vc_(dict.subDict("specie").lookupOrDefault("Vc", -1.0)),
    Pc_(dict.subDict("specie").lookupOrDefault("Pc", -1.0)),
    omega_(dict.subDict("specie").lookupOrDefault("omega", -2.0))
{
    auto eosDict = dict.subDictPtr("equationOfState");
    if (eosDict not_eq nullptr) {
        List<word> oldKeyWords({"Tc", "Pc", "Vc", "omega"});
        forAll(oldKeyWords, wordIdx) {
            if (eosDict->found(oldKeyWords[wordIdx])) {
                WarningIn(__PRETTY_FUNCTION__) << "EOS parameter " << oldKeyWords[wordIdx]
                                               << " has been moved to \"specie\" dict. This change is introduced in OpenFOAMCE because they are eigen properties of specie. Your input will not take effect."
                                               << endl;
            }
        }
    }

}

Foam::word Foam::specie::checkForRealGasEOS(bool checkOmega) const {
    if(this->W()<=0) {
        return "Invalid molecular weight: "+::Foam::name(this->W())+"[kg/kmol]";
    }
    if(this->Tc()<=0) {
        return "Invalid critical temperature: "+::Foam::name(this->Tc()) +"[K]";
    }
    if(this->Pc()<=0) {
        return "Invalid critical pressure: "+::Foam::name(this->Pc())+"[Pa]";
    }
    if(this->Vc()<=0) {
        return "Invalid critical volume: "+::Foam::name(this->Vc())+"[m^3/kmol]";
    }
    if((this->Zc()<=0) or (this->Zc()>1)) {
        return "Invalid critical compression factor: "+::Foam::name(this->Pc());
    }
    if(checkOmega and (this->omega()<=-1)) {
        return "Invalid acentric factor: "+::Foam::name(this->omega());
    }
    return "";
}


void Foam::specie::requireRealGasEOS(bool requireOmega) const {
    word err=this->checkForRealGasEOS(requireOmega);
    if(not err.empty()) {
        FatalErrorInFunction<<this->name()<<" is invalid specie: "<<err<<endl;

        ::Foam::abort(::Foam::FatalError);
    }
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::specie::write(Ostream& os) const
{
    dictionary dict("specie");
    if (Y_ != 1)
    {
        dict.add("massFraction", Y_);
    }
    dict.add("molWeight", molWeight_);
    if(Tc_>0) {
        dict.add("Tc", Tc_);
    }
    if(Pc_>0) {
        dict.add("Pc",Pc_);
    }
    if(Vc_>0) {
        dict.add("Vc",Vc_);
    }
    if(omega_>-1) {
        dict.add("omega", omega_);
    }
    os  << indent << dict.dictName() << dict;
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

Foam::Ostream& Foam::operator<<(Ostream& os, const specie& st)
{
    st.write(os);
    os.check("Ostream& operator<<(Ostream& os, const specie& st)");
    return os;
}


// ************************************************************************* //

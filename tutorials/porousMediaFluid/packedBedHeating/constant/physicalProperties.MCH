FoamFile {
    class dictionary;
    format ascii;
    object physicalProperties.MCH;
}

thermoType
{
    type            heSolidThermo;
    mixture         pureMixture;
    transport       constIsoSolid;
    thermo          eConst;
    equationOfState rhoConst;
    specie          specie;
    energy          sensibleInternalEnergy;
}

mixture
{
    // Aluminium

    specie
    {
        molWeight       98.1861;
    }
    equationOfState
    {
        rho             4.40;
    }
    transport
    {
        kappa           0.1;
    }
    thermodynamics
    {
        hf              0;
        Cv              1307.578;
    }
}
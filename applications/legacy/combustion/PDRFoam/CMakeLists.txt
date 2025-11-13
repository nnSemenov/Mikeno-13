lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name PDRFoam)

add_executable(${target_name}
    psiuMulticomponentThermo/psiuMulticomponentThermo.C
    psiuMulticomponentThermo/psiuMulticomponentThermos.C

    psiuMulticomponentThermo/derivedFvPatchFields/fixedUnburntEnthalpy/fixedUnburntEnthalpyFvPatchScalarField.C
    psiuMulticomponentThermo/derivedFvPatchFields/gradientUnburntEnthalpy/gradientUnburntEnthalpyFvPatchScalarField.C
    psiuMulticomponentThermo/derivedFvPatchFields/mixedUnburntEnthalpy/mixedUnburntEnthalpyFvPatchScalarField.C

    XiModels/XiModel/XiModel.C
    XiModels/XiModel/XiModelNew.C
    XiModels/fixed/fixed.C
    XiModels/algebraic/algebraic.C
    XiModels/transport/transport.C

    XiModels/XiEqModels/XiEqModel/XiEqModel.C
    XiModels/XiEqModels/XiEqModel/XiEqModelNew.C
    XiModels/XiEqModels/Gulder/Gulder.C
    XiModels/XiEqModels/instabilityXiEq/instabilityXiEq.C
    XiModels/XiEqModels/SCOPEBlendXiEq/SCOPEBlendXiEq.C
    XiModels/XiEqModels/SCOPEXiEq/SCOPEXiEq.C

    XiModels/XiGModels/XiGModel/XiGModel.C
    XiModels/XiGModels/XiGModel/XiGModelNew.C
    XiModels/XiGModels/KTS/KTS.C
    XiModels/XiGModels/instabilityG/instabilityG.C

    PDRModels/turbulence/PDRkEpsilon/PDRkEpsilon.C

    PDRModels/dragModels/PDRDragModel/PDRDragModel.C
    PDRModels/dragModels/PDRDragModel/PDRDragModelNew.C
    PDRModels/dragModels/basic/basic.C

    PDRModels/XiEqModels/basicXiSubXiEq/basicXiSubXiEq.C
    PDRModels/XiGModels/basicXiSubG/basicXiSubG.C

    laminarFlameSpeed/laminarFlameSpeed/laminarFlameSpeed.C
    laminarFlameSpeed/laminarFlameSpeed/laminarFlameSpeedNew.C
    laminarFlameSpeed/constant/constant.C
    laminarFlameSpeed/Gulder/Gulder.C
    laminarFlameSpeed/RaviPetersen/RaviPetersen.C
    laminarFlameSpeed/SCOPE/SCOPELaminarFlameSpeed.C

    derivedFvPatchFields/activeBaffleVelocity/activeBaffleVelocityFvPatchVectorField.C
    derivedFvPatchFields/activePressureForceBaffleVelocity/activePressureForceBaffleVelocityFvPatchVectorField.C

    ignition/ignition.C
    ignition/ignitionIO.C
    ignition/ignitionSite.C
    ignition/ignitionSiteIO.C

    PDRFoam.C
)

target_include_directories(${target_name} PRIVATE
    lnInclude

    psiuMulticomponentThermo 
    psiuMulticomponentThermo/derivedFvPatchFields/fixedUnburntEnthalpy 
    psiuMulticomponentThermo/derivedFvPatchFields/gradientUnburntEnthalpy 
    psiuMulticomponentThermo/derivedFvPatchFields/mixedUnburntEnthalpy 
    psiuMulticomponentThermo/mixtures/homogeneousMixture 
    psiuMulticomponentThermo/mixtures/inhomogeneousMixture 
    psiuMulticomponentThermo/mixtures/leanInhomogeneousMixture 
    psiuMulticomponentThermo/mixtures/inhomogeneousEGRMixture 
    XiModels/transport 
    XiModels/fixed 
    XiModels/algebraic 
    XiModels/XiModel 
    XiModels/XiEqModels/XiEqModel 
    XiModels/XiEqModels/Gulder 
    XiModels/XiEqModels/instabilityXiEq 
    XiModels/XiEqModels/SCOPEBlendXiEq 
    XiModels/XiEqModels/SCOPEXiEq 
    XiModels/XiGModels/XiGModel 
    XiModels/XiGModels/instabilityG 
    XiModels/XiGModels/KTS 
    PDRModels/dragModels/basic 
    PDRModels/dragModels/PDRDragModel 
    PDRModels/XiEqModels/basicXiSubXiEq 
    PDRModels/XiGModels/basicXiSubG 
    PDRModels/turbulence/PDRkEpsilon 
    ignition 
    laminarFlameSpeed/laminarFlameSpeed 
    laminarFlameSpeed/SCOPE 
#    ${LIB_SRC}/physicalProperties/lnInclude
    ${LIB_SRC}/thermophysicalModels/specie/lnInclude 
    ${LIB_SRC}/thermophysicalModels/basic/lnInclude 
    ${LIB_SRC}/thermophysicalModels/multicomponentThermo/lnInclude 
    ${LIB_SRC}/MomentumTransportModels/momentumTransportModels/lnInclude 
    ${LIB_SRC}/MomentumTransportModels/compressible/lnInclude 
    ${LIB_SRC}/ThermophysicalTransportModels/thermophysicalTransportModel/lnInclude 
    ${LIB_SRC}/ThermophysicalTransportModels/fluid/lnInclude 
    ${LIB_SRC}/ThermophysicalTransportModels/fluidThermo/lnInclude 
#    ${LIB_SRC}/finiteVolume/lnInclude
    ${LIB_SRC}/meshTools/lnInclude 
    ${LIB_SRC}/triSurface/lnInclude 
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OSspecific
    OpenFOAM

    physicalProperties
    meshTools
    fluidThermophysicalModels 
    multicomponentThermophysicalModels 
    specie 
    momentumTransportModels
    thermophysicalTransportModel
    fluidThermoThermophysicalTransportModels
    fluidThermophysicalTransportModel
    compressibleMomentumTransportModels 
    coupledThermophysicalTransportModels 
    finiteVolume 
    fvModels 
    fvConstraints

    Pstream_best
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=libNULL.so
)

set(FOAM_regular_executables "${FOAM_regular_executables};${target_name}" PARENT_SCOPE)
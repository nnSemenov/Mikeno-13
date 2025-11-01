lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name PDRFoam)

add_executable(${target_name}
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
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OSspecific
    OpenFOAM

    meshTools
    fluidThermophysicalModels
    multicomponentThermophysicalModels
    specie
    momentumTransportModels
    compressibleMomentumTransportModels
    coupledThermophysicalTransportModels
    laminarFlameSpeedModels
    finiteVolume
    fvModels
    fvConstraints
    Pstream_dummy
    coupledThermophysicalTransportModels
    fluidMulticomponentThermophysicalTransportModels
    fluidThermoThermophysicalTransportModels
    thermophysicalTransportModel
    physicalProperties
    fluidThermophysicalTransportModel
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=libNULL.so
)

set(FOAM_regular_executables "${FOAM_regular_executables};${target_name}" PARENT_SCOPE)
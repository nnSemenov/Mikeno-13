lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name XiFluid)

add_library(${target_name} SHARED
    SuModels/SuModel/SuModel.C
    SuModels/SuModel/SuModelNew.C
    SuModels/uniformConstant/uniformConstant_SuModel.C
    SuModels/unstrained/unstrained.C
    SuModels/linearEquilibrium/linearEquilibrium_SuModel.C
    SuModels/transport/transport_SuModel.C

    XiModels/XiModel/XiModel.C
    XiModels/XiModel/XiModelNew.C
    XiModels/uniformConstant/uniformConstant.C
    XiModels/equilibrium/equilibrium.C
    XiModels/transport/transport.C

    XiModels/XiEqModels/XiEqModel/XiEqModel.C
    XiModels/XiEqModels/XiEqModel/XiEqModelNew.C
    XiModels/XiEqModels/constant/constant.C
    XiModels/XiEqModels/Gulder/Gulder.C
    XiModels/XiEqModels/instability/instability.C

    XiModels/XiProfiles/XiProfile/XiProfile.C
    XiModels/XiProfiles/XiProfile/XiProfileNew.C
    XiModels/XiProfiles/uniform/uniform.C
    XiModels/XiProfiles/linear/linear.C
    XiModels/XiProfiles/cubic/cubic.C

    XiModels/XiGModels/XiGModel/XiGModel.C
    XiModels/XiGModels/XiGModel/XiGModelNew.C
    XiModels/XiGModels/KTS/KTS.C
    XiModels/XiGModels/instability/instability_XiGModel.C

    fvModels/ignition/XiCorrModels/XiCorrModel/XiCorrModel.C
    fvModels/ignition/XiCorrModels/XiCorrModel/XiCorrModelNew.C
    fvModels/ignition/XiCorrModels/planar/planarXiCorr.C
    fvModels/ignition/XiCorrModels/cylindrical/cylindricalXiCorr.C
    fvModels/ignition/XiCorrModels/spherical/sphericalXiCorr.C

    fvModels/ignition/bXiIgnition/bXiIgnition.C
    fvModels/ignition/bXiIgnited/bXiIgnited.C
    fvModels/ignition/constantbXiIgnition/constantbXiIgnition.C
    fvModels/ignition/multiCycleConstantbXiIgnition/multiCycleConstantbXiIgnition.C

    XiFluid.C
    thermophysicalPredictor.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_include_directories(${target_name} PRIVATE
    ${LIB_SRC}/physicalProperties/lnInclude
    ${LIB_SRC}/MomentumTransportModels/momentumTransportModels/lnInclude
    ${LIB_SRC}/MomentumTransportModels/compressible/lnInclude
    ${LIB_SRC}/ThermophysicalTransportModels/thermophysicalTransportModel/lnInclude
    ${LIB_SRC}/ThermophysicalTransportModels/fluid/lnInclude
    ${LIB_SRC}/ThermophysicalTransportModels/fluidThermo/lnInclude
    ${LIB_SRC}/thermophysicalModels/specie/lnInclude
    ${LIB_SRC}/thermophysicalModels/basic/lnInclude
    ${LIB_SRC}/thermophysicalModels/multicomponentThermo/lnInclude
    ${LIB_SRC}/thermophysicalModels/laminarFlameSpeed/lnInclude

)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    fluidSolver 
    isothermalFluid 
    momentumTransportModels 
    compressibleMomentumTransportModels 
    fluidThermoThermophysicalTransportModels 
    coupledThermophysicalTransportModels 
    multicomponentThermophysicalModels 
    specie 
    laminarFlameSpeedModels 
    finiteVolume 
    fvModels 
    fvConstraints 
    sampling 
    meshTools
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



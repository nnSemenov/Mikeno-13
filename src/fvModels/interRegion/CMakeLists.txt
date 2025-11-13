lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name interRegionFvModels)

add_library(${target_name} SHARED
    interRegionModel/interRegionModel.C
    interRegionPorosityForce/interRegionPorosityForce.C
    interRegionHeatTransfer/interRegionHeatTransfer.C

    heatTransfer/heatTransfer.C
    heatTransfer/heatTransferAv/heatTransferAv.C

    heatTransferCoefficientModels/heatTransferCoefficientModel/heatTransferCoefficientModel.C
    heatTransferCoefficientModels/constant/constant.C
    heatTransferCoefficientModels/function1/function1.C
    heatTransferCoefficientModels/function2/function2.C
    heatTransferCoefficientModels/variable/variable.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_include_directories(${target_name} PRIVATE
    ${LIB_SRC}/physicalProperties/lnInclude
    ${LIB_SRC}/thermophysicalModels/basic/lnInclude
    ${LIB_SRC}/thermophysicalModels/specie/lnInclude
    ${LIB_SRC}/ThermophysicalTransportModels/fluid/lnInclude
    ${LIB_SRC}/ThermophysicalTransportModels/thermophysicalTransportModel/lnInclude
    ${LIB_SRC}
    ${LIB_SRC}
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    finiteVolume 
    sampling 
    meshTools 
    momentumTransportModels 
    compressibleMomentumTransportModels 
    fluidThermoThermophysicalTransportModels
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



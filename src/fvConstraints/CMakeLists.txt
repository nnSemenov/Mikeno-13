lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name fvConstraints)

add_library(${target_name} SHARED
    fixedValue/fixedValueConstraint.C
    fixedTemperature/fixedTemperature.C
    limitTemperature/limitTemperature.C
    limitPressure/limitPressure.C
    limitMag/limitMag.C
    bound/boundConstraint.C
    meanVelocityForce/meanVelocityForce.C
    meanVelocityForce/patchMeanVelocityForce/patchMeanVelocityForce.C
    zeroDimensionalFixedPressure/zeroDimensionalFixedPressureConstraint.C
    zeroDimensionalFixedPressure/zeroDimensionalFixedPressureModel.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_include_directories(${target_name} PRIVATE
    ${LIB_SRC}/thermophysicalModels/basic/lnInclude
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
    physicalProperties
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



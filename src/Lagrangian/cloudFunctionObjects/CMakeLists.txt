lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name LagrangianCloudFunctionObjects)

add_library(${target_name} SHARED
    cloudPosition/cloudPosition.C

    cloudVolume/cloudVolume.C
    cloudSurfaceArea/cloudSurfaceArea.C
    cloudMass/cloudMass.C

    cloudVolumeFraction/cloudVolumeFraction.C
    cloudSurfaceAreaPerUnitVolume/cloudSurfaceAreaPerUnitVolume.C

    cloudLagrangianVolumeFraction/cloudLagrangianVolumeFraction.C

    cloudAge/cloudAge.C

    cloudKineticEnergy/cloudKineticEnergy.C
    cloudGravitationalPotentialEnergy/cloudGravitationalPotentialEnergy.C

    cloudFlux/cloudFlux.C
    cloudFlux/cloudNumberFlux.C
    cloudFlux/cloudVolumeFlux.C
    cloudFlux/cloudMassFlux.C

    cloudBoundaryCollisionFlux/cloudBoundaryCollisionFlux.C
    cloudBoundaryCollisionFlux/cloudBoundaryCollisionNumberFlux.C
    cloudBoundaryCollisionFlux/cloudBoundaryCollisionForce.C

    cloudSurfaceDistribution/cloudSurfaceDistribution.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_include_directories(${target_name} PRIVATE

)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    finiteVolume 
    meshTools 
    sampling 
    physicalProperties 
    Lagrangian 
    LagrangianFunctionObjects 
    LagrangianCloud
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



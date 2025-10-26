lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name snappyHexMesh)

add_library(${target_name} SHARED
    snappyHexMeshDriver/snappyLayerDriver.C
    # snappyHexMeshDriver/snappyLayerDriverShrink.C
    snappyHexMeshDriver/snappySnapDriver.C
    snappyHexMeshDriver/snappySnapDriverFeature.C
    snappyHexMeshDriver/snappyRefineDriver.C

    snappyHexMeshDriver/layerParameters/layerParameters.C
    snappyHexMeshDriver/refinementParameters/refinementParameters.C
    snappyHexMeshDriver/snapParameters/snapParameters.C
    snappyHexMeshDriver/pointData/pointData.C

    meshRefinement/meshRefinementBaffles.C
    meshRefinement/meshRefinement.C
    meshRefinement/meshRefinementMerge.C
    meshRefinement/meshRefinementProblemCells.C
    meshRefinement/meshRefinementRefine.C

    refinementFeatures/refinementFeatures.C
    refinementSurfaces/surfaceZonesInfo.C
    refinementSurfaces/refinementSurfaces.C
    refinementRegions/refinementRegions.C
    trackedParticle/trackedParticle.C

    motionSmoother/motionSmoother.C
    motionSmoother/motionSmootherAlgo.C
    motionSmoother/motionSmootherData.C

    externalDisplacementMeshMover/displacementMeshMoverMotionSolver.C
    externalDisplacementMeshMover/externalDisplacementMeshMover.C
    externalDisplacementMeshMover/medialAxisMeshMover.C
    externalDisplacementMeshMover/zeroFixedValue/zeroFixedValuePointPatchFields.C

)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)


target_include_directories(${target_name} PRIVATE
    ${LIB_SRC}/parallel/decompose/decompositionMethods/lnInclude
    ${LIB_SRC}/tracking/lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    polyTopoChange 
    motionSolvers 
    finiteVolume 
    lagrangian 
    meshTools 
    meshCheck 
    fileFormats 
    surfMesh 
    triSurface 
    distributed
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



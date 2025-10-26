lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name fvMotionSolvers)

add_library(${target_name} SHARED
    fvMotionSolvers/fvMotionSolver/fvMotionSolver.C
    fvMotionSolvers/displacement/SBRStress/displacementSBRStressFvMotionSolver.C
    fvMotionSolvers/displacement/laplacian/displacementLaplacianFvMotionSolver.C

    fvMotionSolvers/componentDisplacement/componentLaplacian/displacementComponentLaplacianFvMotionSolver.C

    fvMotionSolvers/velocity/laplacian/velocityLaplacianFvMotionSolver.C

    fvMotionSolvers/componentVelocity/componentLaplacian/velocityComponentLaplacianFvMotionSolver.C

    motionDiffusivity/motionDiffusivity/motionDiffusivity.C
    motionDiffusivity/uniform/uniformDiffusivity.C
    motionDiffusivity/inverseDistance/inverseDistanceDiffusivity.C
    motionDiffusivity/inverseFaceDistance/inverseFaceDistanceDiffusivity.C
    motionDiffusivity/inversePointDistance/inversePointDistanceDiffusivity.C
    motionDiffusivity/inverseVolume/inverseVolumeDiffusivity.C
    motionDiffusivity/directional/directionalDiffusivity.C
    motionDiffusivity/motionDirectional/motionDirectionalDiffusivity.C
    motionDiffusivity/file/fileDiffusivity.C

    motionDiffusivity/manipulators/quadratic/quadraticDiffusivity.C
    motionDiffusivity/manipulators/exponential/exponentialDiffusivity.C

    fvPatchFields/derived/cellMotion/cellMotionFvPatchFields.C
    fvPatchFields/derived/surfaceSlipDisplacement/surfaceSlipDisplacementFvPatchFields.C
)

set(derivedPoint pointPatchFields/derived)
target_sources(${target_name} PRIVATE
    ${derivedPoint}/oscillatingVelocity/oscillatingVelocityPointPatchVectorField.C
    ${derivedPoint}/angularOscillatingVelocity/angularOscillatingVelocityPointPatchVectorField.C

    ${derivedPoint}/oscillatingDisplacement/oscillatingDisplacementPointPatchVectorField.C
    ${derivedPoint}/angularOscillatingDisplacement/angularOscillatingDisplacementPointPatchVectorField.C
    ${derivedPoint}/surfaceSlipDisplacement/surfaceSlipDisplacementPointPatchVectorField.C
    ${derivedPoint}/surfaceDisplacement/surfaceDisplacementPointPatchVectorField.C
    ${derivedPoint}/waveDisplacement/waveDisplacementPointPatchVectorField.C

    ${derivedPoint}/timeVaryingMappedFixedValue/timeVaryingMappedFixedValuePointPatchFields.C
    ${derivedPoint}/uniformInterpolatedDisplacement/uniformInterpolatedDisplacementPointPatchVectorField.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    triSurface 
    meshTools 
    motionSolvers 
    motionSolver_fvMeshMover 
    finiteVolume 
    fileFormats
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



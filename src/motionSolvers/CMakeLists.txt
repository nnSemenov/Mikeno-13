lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name motionSolvers)

add_library(${target_name} SHARED
    motionSolver/motionSolver.C
    displacement/points0/points0MotionSolver.C
    displacement/displacement/displacementMotionSolver.C
    displacement/layeredSolver/displacementLayeredMotionSolver.C
    displacement/layeredSolver/pointEdgeStructuredWalk.C
    displacement/linearSolver/displacementLinearMotionSolver.C
    componentDisplacement/componentDisplacementMotionSolver.C
    velocity/velocityMotionSolver.C
    componentVelocity/componentVelocityMotionSolver.C
    displacement/solidBody/solidBodyMotionSolver/solidBodyMotionSolver.C
    displacement/solidBody/multiSolidBodyMotionSolver/multiSolidBodyMotionSolver.C
    displacement/solidBody/interpolatingSolidBodyMotionSolver/interpolatingSolidBodyMotionSolver.C
    motionSolverList/motionSolverList.C
)

set(solidBodyMotionFunctions displacement/solidBody/solidBodyMotionFunctions)
target_sources(${target_name} PRIVATE
    ${solidBodyMotionFunctions}/solidBodyMotionFunction/solidBodyMotionFunction.C
    ${solidBodyMotionFunctions}/solidBodyMotionFunction/solidBodyMotionFunctionNew.C
    ${solidBodyMotionFunctions}/SDA/SDA.C
    ${solidBodyMotionFunctions}/sixDoFMotion/sixDoFMotion.C
    ${solidBodyMotionFunctions}/linearMotion/linearMotion.C
    ${solidBodyMotionFunctions}/rotatingMotion/rotatingMotion.C
    ${solidBodyMotionFunctions}/axisRotationMotion/axisRotationMotion.C
    ${solidBodyMotionFunctions}/multiMotion/multiMotion.C
    ${solidBodyMotionFunctions}/oscillatingLinearMotion/oscillatingLinearMotion.C
    ${solidBodyMotionFunctions}/oscillatingRotatingMotion/oscillatingRotatingMotion.C

    displacement/solidBody/pointPatchFields/derived/solidBodyMotionDisplacement/solidBodyMotionDisplacementPointPatchVectorField.C

    pointInterpolator/dynamicMeshPointInterpolator.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    finiteVolume
    meshTools
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



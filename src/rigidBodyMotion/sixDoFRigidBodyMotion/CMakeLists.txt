lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name sixDoFRigidBodyMotion)

add_library(${target_name} SHARED
    sixDoFRigidBodyMotion/sixDoFRigidBodyMotion.C
    sixDoFRigidBodyMotion/sixDoFRigidBodyMotionIO.C
    sixDoFRigidBodyMotion/sixDoFRigidBodyMotionState.C
    sixDoFRigidBodyMotion/sixDoFRigidBodyMotionStateIO.C
)

set(restraints sixDoFRigidBodyMotion/restraints)
target_sources(${target_name} PRIVATE
    ${restraints}/sixDoFRigidBodyMotionRestraint/sixDoFRigidBodyMotionRestraint.C
    ${restraints}/sixDoFRigidBodyMotionRestraint/sixDoFRigidBodyMotionRestraintNew.C
    ${restraints}/linearAxialAngularSpring/linearAxialAngularSpring.C
    ${restraints}/linearSpring/linearSpring.C
    ${restraints}/sphericalAngularSpring/sphericalAngularSpring.C
    ${restraints}/axialAngularSpring/axialAngularSpring.C
    ${restraints}/linearDamper/linearDamper.C
    ${restraints}/sphericalAngularDamper/sphericalAngularDamper.C
)

set(constraints sixDoFRigidBodyMotion/constraints)
target_sources(${target_name} PRIVATE
    ${constraints}/sixDoFRigidBodyMotionConstraint/sixDoFRigidBodyMotionConstraint.C
    ${constraints}/sixDoFRigidBodyMotionConstraint/sixDoFRigidBodyMotionConstraintNew.C
    ${constraints}/axis/sixDoFRigidBodyMotionAxisConstraint.C
    ${constraints}/line/sixDoFRigidBodyMotionLineConstraint.C
    ${constraints}/orientation/sixDoFRigidBodyMotionOrientationConstraint.C
    ${constraints}/plane/sixDoFRigidBodyMotionPlaneConstraint.C
    ${constraints}/point/sixDoFRigidBodyMotionPointConstraint.C

    sixDoFRigidBodyMotionSolver/sixDoFRigidBodyMotionSolver.C

    sixDoFSolvers/sixDoFSolver/sixDoFSolver.C
    sixDoFSolvers/sixDoFSolver/sixDoFSolverNew.C
    sixDoFSolvers/symplectic/symplectic.C
    sixDoFSolvers/CrankNicolson/CrankNicolson.C
    sixDoFSolvers/Newmark/Newmark.C

)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_include_directories(${target_name} PRIVATE
    ${LIB_SRC}/finiteVolume/lnInclude
    ${LIB_SRC}/motionSolvers/lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    forces 
    meshTools 
    fileFormats 
    motionSolver_fvMeshMover
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



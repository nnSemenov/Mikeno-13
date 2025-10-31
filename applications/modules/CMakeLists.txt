add_subdirectory(movingMesh)
add_subdirectory(functions)
add_subdirectory(fluidSolver)
add_subdirectory(incompressibleFluid)
add_subdirectory(isothermalFluid)
add_subdirectory(fluid)
add_subdirectory(multicomponentFluid)
add_subdirectory(porousMediaFluid)
add_subdirectory(XiFluid)
add_subdirectory(shockFluid)

add_subdirectory(VoFSolver)
add_subdirectory(twoPhaseSolver)
add_subdirectory(twoPhaseVoFSolver)

add_subdirectory(incompressibleVoF)

set(FOAM_regular_libraries ${FOAM_regular_libraries} PARENT_SCOPE)
set(FOAM_special_libraries ${FOAM_special_libraries} PARENT_SCOPE)
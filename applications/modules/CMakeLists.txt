add_subdirectory(movingMesh)
add_subdirectory(functions)
add_subdirectory(fluidSolver)
add_subdirectory(incompressibleFluid)


set(FOAM_regular_libraries ${FOAM_regular_libraries} PARENT_SCOPE)
set(FOAM_special_libraries ${FOAM_special_libraries} PARENT_SCOPE)
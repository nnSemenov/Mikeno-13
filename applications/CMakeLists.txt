set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)

add_subdirectory(solvers/foamRun)
add_subdirectory(solvers/foamMultiRun)
add_subdirectory(solvers/chemFoam)
add_subdirectory(solvers/potentialFoam)
add_subdirectory(solvers/boundaryFoam)

add_subdirectory(modules)

add_subdirectory(legacy)

add_subdirectory(utilities)
###############################################

set(FOAM_regular_executables ${FOAM_regular_executables} PARENT_SCOPE)
set(FOAM_regular_libraries ${FOAM_regular_libraries} PARENT_SCOPE)
set(FOAM_special_libraries ${FOAM_special_libraries} PARENT_SCOPE)

add_subdirectory(test)
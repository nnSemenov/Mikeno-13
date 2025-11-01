add_subdirectory(basic/laplacianFoam)
add_subdirectory(basic/financialFoam)

set(FOAM_regular_executables ${FOAM_regular_executables} PARENT_SCOPE)
set(FOAM_regular_libraries ${FOAM_regular_libraries} PARENT_SCOPE)
set(FOAM_special_libraries ${FOAM_special_libraries} PARENT_SCOPE)
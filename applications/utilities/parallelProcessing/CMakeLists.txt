add_subdirectory(decomposePar)
add_subdirectory(reconstructPar)
add_subdirectory(redistributePar)

set(FOAM_regular_executables ${FOAM_regular_executables} PARENT_SCOPE)
set(FOAM_regular_libraries ${FOAM_regular_libraries} PARENT_SCOPE)
add_subdirectory(decompositionMethods)
add_subdirectory(metis)
add_subdirectory(parMetis)
add_subdirectory(scotch)
add_subdirectory(ptscotch)
add_subdirectory(zoltan)


set(FOAM_regular_libraries ${FOAM_regular_libraries} PARENT_SCOPE)
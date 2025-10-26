add_subdirectory(decompositionMethods)
add_subdirectory(metis)
add_subdirectory(scotch)

message(WARNING "TODO: Migrate more decomposition methods")

set(FOAM_regular_libraries ${FOAM_regular_libraries} PARENT_SCOPE)
add_subdirectory(mesh)
add_subdirectory(miscellaneous)
add_subdirectory(parallelProcessing)
add_subdirectory(postProcessing)
add_subdirectory(preProcessing)
message(WARNING "TODO: Migrate proProcessing")


set(FOAM_regular_executables ${FOAM_regular_executables} PARENT_SCOPE)
set(FOAM_regular_libraries ${FOAM_regular_libraries} PARENT_SCOPE)
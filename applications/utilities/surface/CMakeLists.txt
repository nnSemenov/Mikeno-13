add_subdirectory(surfaceAdd)
add_subdirectory(surfaceAutoPatch)
add_subdirectory(surfaceBooleanFeatures)
add_subdirectory(surfaceCheck)


set(FOAM_regular_executables ${FOAM_regular_executables} PARENT_SCOPE)
set(FOAM_regular_libraries ${FOAM_regular_libraries} PARENT_SCOPE)
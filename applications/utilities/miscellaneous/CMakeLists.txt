add_subdirectory(foamDictionary)
add_subdirectory(foamFormatConvert)
add_subdirectory(foamListTimes)
add_subdirectory(foamToC)
add_subdirectory(patchSummary)
add_subdirectory(autoCompress)

set(FOAM_regular_executables ${FOAM_regular_executables} PARENT_SCOPE)
set(FOAM_regular_libraries ${FOAM_regular_libraries} PARENT_SCOPE)
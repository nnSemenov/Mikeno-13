add_subdirectory(dataConversion)
add_subdirectory(foamPostProcess)

add_subdirectory(graphics)

add_subdirectory(lagrangian/particleTracks)
add_subdirectory(lagrangian/steadyParticleTracks)

add_subdirectory(miscellaneous/engineCompRatio)
add_subdirectory(miscellaneous/pdfPlot)
add_subdirectory(miscellaneous/temporalInterpolate)

set(FOAM_regular_executables ${FOAM_regular_executables} PARENT_SCOPE)
set(FOAM_regular_libraries ${FOAM_regular_libraries} PARENT_SCOPE)
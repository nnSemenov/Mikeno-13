add_subdirectory(adiabaticFlameT)
add_subdirectory(chemkinToFoam)
add_subdirectory(equilibriumCO)
add_subdirectory(equilibriumFlameT)
add_subdirectory(mixtureAdiabaticFlameT)

set(FOAM_regular_executables ${FOAM_regular_executables} PARENT_SCOPE)
set(FOAM_regular_libraries ${FOAM_regular_libraries} PARENT_SCOPE)

add_subdirectory(basic)
add_subdirectory(solidParticle)
add_subdirectory(parcel)
add_subdirectory(DSMC)
add_subdirectory(molecularDynamics)
add_subdirectory(functionObjects)

set(FOAM_regular_libraries ${FOAM_regular_libraries} PARENT_SCOPE)
add_subdirectory(general)
add_subdirectory(interRegion)
add_subdirectory(rotorDisk)
add_subdirectory(propellerDisk)
add_subdirectory(rigidBodyPropellerDisk)

set(FOAM_regular_libraries ${FOAM_regular_libraries} PARENT_SCOPE)

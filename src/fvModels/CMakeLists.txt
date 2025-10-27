add_subdirectory(general)
add_subdirectory(interRegion)
add_subdirectory(rotorDisk)

message(WARNING "TODO: Consider resurrect propellerDisk")
#add_subdirectory(propellerDisk)

set(FOAM_regular_libraries ${FOAM_regular_libraries} PARENT_SCOPE)

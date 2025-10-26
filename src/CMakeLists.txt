
# libraries that are installed to lib.
set(FOAM_regular_libraries)
# libraries that don't install to lib, but different destination
set(FOAM_special_libraries)

lnInclude(OpenFOAM RESULT_DIR OpenFOAM_lnInclude_dir)
message(STATUS "OpenFOAM_lnInclude_dir = ${OpenFOAM_lnInclude_dir}")

add_subdirectory(OSspecific/POSIX)
add_subdirectory(Pstream)
add_subdirectory(OpenFOAM)

add_subdirectory(fileFormats)
add_subdirectory(surfMesh)
add_subdirectory(triSurface)
add_subdirectory(meshTools)

add_subdirectory(finiteVolume)

add_subdirectory(ODE)
add_subdirectory(physicalProperties)
add_subdirectory(thermophysicalModels)

add_subdirectory(tracking)
add_subdirectory(lagrangian/basic)
add_subdirectory(Lagrangian/Lagrangian)

add_subdirectory(generic)

add_subdirectory(sampling)
add_subdirectory(meshCheck)
add_subdirectory(topoSetSources)
add_subdirectory(fvTopoSetSources)

add_subdirectory(motionSolvers)

add_subdirectory(mesh/extrudeModel)
add_subdirectory(polyTopoChange)

add_subdirectory(conversion)

add_subdirectory(parallel)

add_subdirectory(fvMeshStitchers)
#add_subdirectory(fvMeshMovers)
#add_subdirectory(fvMeshTopoChangers)
#add_subdirectory(fvMeshDistributors)



###############################################

message(STATUS "Regular libraries: ${FOAM_regular_libraries}")
message(STATUS "Non-regular libraries: ${FOAM_special_libraries}")

install(TARGETS ${FOAM_regular_libraries}
    DESTINATION lib
)
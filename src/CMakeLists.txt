


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
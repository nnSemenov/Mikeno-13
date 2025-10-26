

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
add_subdirectory(fvMeshMovers)
add_subdirectory(fvMeshTopoChangers)
add_subdirectory(fvMeshDistributors)

add_subdirectory(randomProcesses)

add_subdirectory(twoPhaseModels)
add_subdirectory(multiphaseModels)
add_subdirectory(MomentumTransportModels)
#MomentumTransportModels/Allwmake $targetType $*
#ThermophysicalTransportModels/Allwmake $targetType $*
#wmake $targetType radiationModels
#wmake $targetType combustionModels
#mesh/Allwmake $targetType $*
#renumber/Allwmake $targetType $*
#fvAgglomerationMethods/Allwmake $targetType $*
#wmake $targetType fvMotionSolver
###############################################

set(FOAM_regular_libraries ${FOAM_regular_libraries} PARENT_SCOPE)
set(FOAM_special_libraries ${FOAM_special_libraries} PARENT_SCOPE)
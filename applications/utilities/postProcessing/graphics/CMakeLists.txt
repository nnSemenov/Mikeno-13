add_subdirectory(ensightFoamReader)

if(ParaView_FOUND)
    add_subdirectory(PVReaders)
else ()
    message(WARNING "TODO: Migrate PVReaders utilities")
    message(STATUS "Skip all utilities under PVReaders because paraview is not found.")
endif ()

set(FOAM_regular_executables ${FOAM_regular_executables} PARENT_SCOPE)
set(FOAM_regular_libraries ${FOAM_regular_libraries} PARENT_SCOPE)
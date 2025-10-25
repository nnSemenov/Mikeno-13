lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

add_library(fvTopoSetSources SHARED
    cellSources/fieldToCell/fieldToCell.C
    faceSources/patchFluxToFace/patchFluxToFace.C
)

target_include_directories(fvTopoSetSources PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_link_libraries(fvTopoSetSources PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    finiteVolume
    meshTools
    topoSetSources
)

target_compile_definitions(fvTopoSetSources PRIVATE
    LIB_NAME=libfvTopoSetSources.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};fvTopoSetSources" PARENT_SCOPE)



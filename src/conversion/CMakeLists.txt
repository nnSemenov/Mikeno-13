lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name conversion)

add_library(${target_name} SHARED
    mergedCyclic/mergedCyclicPolyPatch.C
    mergedCyclic/polyMeshUnMergeCyclics.C

    meshTables/boundaryRegion.C
    meshTables/cellTable.C
    meshTables/dictionaryIOMap.C

    meshReader/meshReader.C
    meshReader/meshReaderAux.C
    meshReader/calcPointCells.C
    meshReader/createPolyCells.C
    meshReader/createPolyBoundary.C
    meshReader/starcd/STARCDMeshReader.C

    meshWriter/meshWriter.C
    meshWriter/starcd/STARCDMeshWriter.C

    polyDualMesh/polyDualMesh.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    fileFormats
    finiteVolume
    polyTopoChange
    meshTools
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



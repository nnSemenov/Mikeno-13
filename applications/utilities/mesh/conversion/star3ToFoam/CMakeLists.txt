lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name star3ToFoam)

add_executable(${target_name}
    coupledFacePair.C
    starMesh.C
    readPoints.C
    # readSeparatedPoints.C
    readCells.C
    readBoundary.C
    fixCollapsedEdges.C
    readCouples.C
    createCoupleMatches.C
    mergeCoupleFacePoints.C
    calcPointCells.C
    createPolyCells.C
    createBoundaryFaces.C
    createPolyBoundary.C
    purgeCellShapes.C
    writeMesh.C
    star3ToFoam.C
)

target_include_directories(${target_name} PRIVATE
    lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OSspecific
    OpenFOAM

    polyTopoChange
    genericPatches
    conversion
    Pstream_best
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=libNULL.so
)

set(FOAM_regular_executables "${FOAM_regular_executables};${target_name}" PARENT_SCOPE)
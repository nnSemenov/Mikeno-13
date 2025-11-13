lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name polyTopoChange)

add_library(${target_name} SHARED
    polyTopoChange/polyTopoChange.C
    polyTopoChange/addPatchCellLayer.C
    polyTopoChange/pointEdgeCollapse/pointEdgeCollapse.C
    polyTopoChange/edgeCollapser.C
    polyTopoChange/removeCells.C
    polyTopoChange/removeFaces.C
    polyTopoChange/refinementData.C
    polyTopoChange/refinementDistanceData.C
    polyTopoChange/removePoints.C
    polyTopoChange/combineFaces.C
    polyTopoChange/duplicatePoints.C
)

set(hexRef8 polyTopoChange/hexRef8)
target_sources(${target_name} PRIVATE
    ${hexRef8}/hexRef8.C
    ${hexRef8}/hexRef8Data.C
    ${hexRef8}/refinementHistory.C
)

target_sources(${target_name} PRIVATE
    perfectInterface/perfectInterface.C
    mergePatchPairs/mergePatchPairs.C

    repatchMesh/repatchMesh.C
    repatchMesh/repatchPatch.C
)

set(meshModifiers meshCut/meshModifiers)
target_sources(${target_name} PRIVATE
    ${meshModifiers}/meshCutter/meshCutter.C
    ${meshModifiers}/undoableMeshCutter/undoableMeshCutter.C
    ${meshModifiers}/refinementIterator/refinementIterator.C
    ${meshModifiers}/multiDirRefinement/multiDirRefinement.C
)

target_sources(${target_name} PRIVATE
    meshCut/cellLooper/cellLooper.C
    meshCut/cellLooper/geomCellLooper.C
    meshCut/cellLooper/hexCellLooper.C
    meshCut/directions/directions.C
    meshCut/directions/directionInfo/directionInfo.C
    meshCut/edgeVertex/edgeVertex.C
    meshCut/cellCuts/cellCuts.C
    meshCut/splitCell/splitCell.C
    meshCut/refineCell/refineCell.C
)

target_sources(${target_name} PRIVATE
    repatcher/repatcher.C

    fvMeshAdder/fvMeshAdder.C
    fvMeshDistribute/fvMeshDistribute.C
    polyMeshAdder/faceCoupleInfo.C
    polyMeshAdder/polyMeshAdder.C

    fvMeshTools/fvMeshTools.C

    fvMeshSubset/fvMeshSubset.C

    createShellMesh/createShellMesh.C

    polyMeshFilter/polyMeshFilterSettings.C
    polyMeshFilter/polyMeshFilter.C
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
    meshTools 
    meshCheck 
    triSurface 
    extrudeModel
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



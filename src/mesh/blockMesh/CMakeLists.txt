lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name blockMesh)

add_library(${target_name} SHARED
    blockVertices/blockVertex/blockVertex.C
    blockVertices/pointVertex/pointVertex.C
    blockVertices/projectVertex/projectVertex.C
    blockVertices/namedVertex/namedVertex.C

    blockEdges/blockEdge/blockEdge.C
    blockEdges/lineDivide/lineDivide.C
    blockEdges/lineEdge/lineEdge.C
    blockEdges/polyLineEdge/polyLine.C
    blockEdges/polyLineEdge/polyLineEdge.C
    blockEdges/arcEdge/arcEdge.C
    blockEdges/BSplineEdge/BSplineEdge.C
    blockEdges/splineEdge/splineEdge.C
    blockEdges/projectEdge/projectEdge.C
    blockEdges/projectCurveEdge/projectCurveEdge.C

    blockFaces/blockFace/blockFace.C
    blockFaces/projectFace/projectFace.C

    gradingDescriptor/gradingDescriptor.C
    gradingDescriptor/gradingDescriptors.C

    blockDescriptor/blockDescriptor.C
    blockDescriptor/blockDescriptorEdges.C

    blocks/block/block.C
    blocks/block/blockCreate.C
    blocks/namedBlock/namedBlock.C

    blockMesh/blockMesh.C
    blockMesh/blockMeshCreate.C
    blockMesh/blockMeshTopology.C
    blockMesh/blockMeshCheck.C
    blockMesh/blockMeshMerge.C
    blockMesh/blockMeshMergeFast.C

    blockMeshTools/blockMeshTools.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    meshTools
    fileFormats
    surfMesh
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



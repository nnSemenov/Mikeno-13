add_subdirectory(advanced/collapseEdges)
add_subdirectory(advanced/combinePatchFaces)
add_subdirectory(advanced/refinementLevel)
add_subdirectory(advanced/refineWallLayer)
add_subdirectory(advanced/removeFaces)
add_subdirectory(advanced/selectCells)
add_subdirectory(advanced/splitCells)

message(WARNING "Migrate all mesh/conversion utilities")

add_subdirectory(generation/blockMesh)
add_subdirectory(generation/extrude2DMesh)
add_subdirectory(generation/extrudeMesh)
add_subdirectory(generation/extrudeToRegionMesh)
add_subdirectory(generation/snappyHexMesh)
add_subdirectory(generation/zeroDimensionalMesh)

set(FOAM_regular_executables ${FOAM_regular_executables} PARENT_SCOPE)
set(FOAM_regular_libraries ${FOAM_regular_libraries} PARENT_SCOPE)
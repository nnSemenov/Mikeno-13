lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

add_library(meshCheck SHARED
    primitiveMeshCheck/primitiveMeshCheck.C
    primitiveMeshCheck/primitiveMeshCheckPointNearness.C
    primitiveMeshCheck/primitiveMeshCheckEdgeLength.C

    polyMeshCheck/polyMeshCheck.C
    polyMeshCheck/polyMeshCheckQuality.C

    mergeAndWrite/mergeAndWrite.C
    checkTopology.C
    checkGeometry.C
    checkMesh.C
)

target_include_directories(meshCheck PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_link_libraries(meshCheck PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    meshTools 
    triSurface 
    surfMesh 
    fileFormats 
    sampling
)

install(TARGETS meshCheck
    DESTINATION lib
)
lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

add_library(topoSetSources SHARED
    topoSets/cellZoneSet.C
    topoSets/faceZoneSet.C
    topoSets/pointZoneSet.C

    topoSetSource/topoSetSource.C

    cellSources/faceToCell/faceToCell.C
    cellSources/pointToCell/pointToCell.C
    cellSources/shapeToCell/shapeToCell.C
    cellSources/boxToCell/boxToCell.C
    cellSources/regionToCell/regionToCell.C
    cellSources/rotatedBoxToCell/rotatedBoxToCell.C
    cellSources/labelToCell/labelToCell.C
    cellSources/surfaceToCell/surfaceToCell.C
    cellSources/cellToCell/cellToCell.C
    cellSources/nearestToCell/nearestToCell.C
    cellSources/nbrToCell/nbrToCell.C
    cellSources/zoneToCell/zoneToCell.C
    cellSources/sphereToCell/sphereToCell.C
    cellSources/cylinderToCell/cylinderToCell.C
    cellSources/faceZoneToCell/faceZoneToCell.C
    cellSources/cylinderAnnulusToCell/cylinderAnnulusToCell.C
    cellSources/targetVolumeToCell/targetVolumeToCell.C
    cellSources/patchDistanceToCell/patchDistanceToCell.C
    cellSources/truncatedConeToCell/truncatedConeToCell.C
    cellSources/hemisphereToCell/hemisphereToCell.C

    faceSources/faceToFace/faceToFace.C
    faceSources/labelToFace/labelToFace.C
    faceSources/cellToFace/cellToFace.C
    faceSources/normalToFace/normalToFace.C
    faceSources/patchToFace/patchToFace.C
    faceSources/pointToFace/pointToFace.C
    faceSources/boundaryToFace/boundaryToFace.C
    faceSources/zoneToFace/zoneToFace.C
    faceSources/boxToFace/boxToFace.C
    faceSources/rotatedBoxToFace/rotatedBoxToFace.C
    faceSources/regionToFace/regionToFace.C
    faceSources/cylinderToFace/cylinderToFace.C
    faceSources/cylinderAnnulusToFace/cylinderAnnulusToFace.C

    pointSources/labelToPoint/labelToPoint.C
    pointSources/pointToPoint/pointToPoint.C
    pointSources/cellToPoint/cellToPoint.C
    pointSources/faceToPoint/faceToPoint.C
    pointSources/boxToPoint/boxToPoint.C
    pointSources/surfaceToPoint/surfaceToPoint.C
    pointSources/zoneToPoint/zoneToPoint.C
    pointSources/nearestToPoint/nearestToPoint.C

    faceZoneSources/faceZoneToFaceZone/faceZoneToFaceZone.C
    faceZoneSources/setsToFaceZone/setsToFaceZone.C
    faceZoneSources/setToFaceZone/setToFaceZone.C
    faceZoneSources/setAndNormalToFaceZone/setAndNormalToFaceZone.C
    faceZoneSources/setAndPointToFaceZone/setAndPointToFaceZone.C
    faceZoneSources/searchableSurfaceToFaceZone/searchableSurfaceToFaceZone.C
    faceZoneSources/planeToFaceZone/planeToFaceZone.C

    cellZoneSources/setToCellZone/setToCellZone.C

    pointZoneSources/setToPointZone/setToPointZone.C

    surfaceSets/surfaceSets.C

    badQualityToCell/badQualityToCell.C
    badQualityToFace/badQualityToFace.C
)

target_include_directories(topoSetSources PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_link_libraries(topoSetSources PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    triSurface
    meshTools
    meshCheck
)

target_compile_definitions(topoSetSources PRIVATE
    LIB_NAME=libtopoSetSources.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};topoSetSources" PARENT_SCOPE)



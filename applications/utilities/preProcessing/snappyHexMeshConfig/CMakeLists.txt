lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name snappyHexMeshConfig)

add_executable(${target_name}
    meshingSurface.C
    meshingSurfaceList.C
    caseFileConfiguration.C
    blockMeshConfigurationBase.C
    blockMeshCartesianConfiguration.C
    blockMeshCylindricalConfiguration.C
    snappyHexMeshConfiguration.C
    meshQualityConfiguration.C
    surfaceFeaturesConfiguration.C
    snappyHexMeshConfig.C
)

target_include_directories(${target_name} PRIVATE
    lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OSspecific
    OpenFOAM

    sampling 
    triSurface 
    fileFormats 
    meshTools 
    blockMesh 
    Pstream_best
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=libNULL.so
)

set(FOAM_regular_executables "${FOAM_regular_executables};${target_name}" PARENT_SCOPE)
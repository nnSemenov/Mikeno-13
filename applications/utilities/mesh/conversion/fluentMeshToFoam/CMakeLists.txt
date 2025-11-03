lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name fluentMeshToFoam)

flex_target(fluentMeshToFoamFlex
    fluentMeshToFoam.L
    fluentMeshToFoam.L.C
    COMPILE_FLAGS "-+ -f"
)

add_executable(${target_name}
    extrudedTriangleCellShape.C
    extrudedQuadCellShape.C
    create3DCellShape.C
    ${FLEX_fluentMeshToFoamFlex_OUTPUTS}
)


target_include_directories(${target_name} PRIVATE
    lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OSspecific
    OpenFOAM

    meshTools
    genericPatches
    polyTopoChange
    Pstream_best
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=libNULL.so
)

set(FOAM_regular_executables "${FOAM_regular_executables};${target_name}" PARENT_SCOPE)
lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name extrude2DMesh)

add_library(${target_name} SHARED
    extrude2DMesh/extrude2DMesh.C

    patchToPoly2DMesh/patchToPoly2DMesh.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_include_directories(${target_name} PRIVATE
    ${LIB_SRC}/mesh/extrudeModel/lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    meshTools
    polyTopoChange
    surfMesh
    finiteVolume
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



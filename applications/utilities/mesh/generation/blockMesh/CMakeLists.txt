lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name blockMesh_exe)

add_executable(${target_name}
    blockMesh.C
)

set_target_properties(blockMesh_exe PROPERTIES
    OUTPUT_NAME blockMesh
)

target_include_directories(${target_name} PRIVATE
    lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OSspecific
    OpenFOAM

    blockMesh
    meshTools
    genericPatches
    fileFormats
    polyTopoChange
    Pstream_best
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=libNULL.so
)

set(FOAM_regular_executables "${FOAM_regular_executables};${target_name}" PARENT_SCOPE)
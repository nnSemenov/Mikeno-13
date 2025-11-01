lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(extrude2DMesh)

set(target_name extrude2DMesh_exe)

add_executable(${target_name}
    extrude2DMesh.C
)

message(WARNING "TODO: Correct output name and solve conflicts")
#set_target_properties(${target_name} PROPERTIES
#    OUTPUT_NAME extrude2DMesh
#
#)

target_include_directories(${target_name} PRIVATE
    lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OSspecific
    OpenFOAM

    surfMesh
    polyTopoChange
    extrude2DMesh
    genericPatches
    extrudeModel
    Pstream_best
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=libNULL.so
)

set(FOAM_regular_executables "${FOAM_regular_executables};${target_name}" PARENT_SCOPE)


set(FOAM_regular_libraries ${FOAM_regular_libraries} PARENT_SCOPE)
lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name patchSummary)

add_executable(${target_name}
    patchSummary.C
)

target_include_directories(${target_name} PRIVATE
    lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OSspecific
    OpenFOAM

    genericFields 
    genericFvFields 
    finiteVolume 
    meshTools 
    Pstream_best
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=libNULL.so
)

set(FOAM_regular_executables "${FOAM_regular_executables};${target_name}" PARENT_SCOPE)
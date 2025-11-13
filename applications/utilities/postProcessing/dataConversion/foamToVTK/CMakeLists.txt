lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(foamToVTK foamToVTK_lib)

set(target_name foamToVTK_exe)

add_executable(${target_name}
    foamToVTK.C
)

set_target_properties(${target_name} PROPERTIES
    OUTPUT_NAME foamToVTK
)

target_include_directories(${target_name} PRIVATE
    lnInclude
    ${LIB_SRC}/tracking/lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OSspecific
    OpenFOAM

    foamToVTK 
    polyTopoChange 
    lagrangian 
    genericFields 
    genericFvFields 
    finiteVolume 
    meshTools 
    Pstream_best
    fileFormats
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=libNULL.so
)

set(FOAM_regular_executables "${FOAM_regular_executables};${target_name}" PARENT_SCOPE)
set(FOAM_regular_libraries "${FOAM_regular_libraries}" PARENT_SCOPE)
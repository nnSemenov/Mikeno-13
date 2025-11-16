lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name autoCompress)

add_executable(${target_name}
    autoCompress.C
)

target_include_directories(${target_name} PRIVATE
    lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OSspecific
    OpenFOAM

    meshTools
    finiteVolume
    genericFvFields
    lagrangian
    ZLIB::ZLIB

    OpenMP::OpenMP_CXX
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=libNULL.so
)

target_compile_features(${target_name} PRIVATE
    cxx_std_23
)

set(FOAM_regular_executables "${FOAM_regular_executables};${target_name}" PARENT_SCOPE)
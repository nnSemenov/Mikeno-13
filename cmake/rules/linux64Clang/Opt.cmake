include(${CMAKE_CURRENT_LIST_DIR}/general.cmake)

target_compile_options(OpenFOAM_Defines INTERFACE
    -march=native
)
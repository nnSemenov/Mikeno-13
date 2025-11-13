include(${CMAKE_CURRENT_LIST_DIR}/general.cmake)

target_compile_definitions(OpenFOAM_Defines INTERFACE
    FULLDEBUG
)

target_compile_options(OpenFOAM_Defines INTERFACE
    -ggdb3
)
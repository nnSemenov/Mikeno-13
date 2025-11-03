lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name fluent3DMeshToFoam)

flex_target(fluent3DMeshToFoamFlex
    fluent3DMeshToFoam.L
    fluent3DMeshToFoam.L.C
    COMPILE_FLAGS "-+ -f"
)

add_executable(${target_name}
    ${FLEX_fluent3DMeshToFoamFlex_OUTPUTS}
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
    conversion
    Pstream_best
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=libNULL.so
)

set(FOAM_regular_executables "${FOAM_regular_executables};${target_name}" PARENT_SCOPE)
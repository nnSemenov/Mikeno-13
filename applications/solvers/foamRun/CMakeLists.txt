lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name foamRun)

add_executable(${target_name}
    setDeltaT.C
    foamRun.C
)

target_include_directories(${target_name} PRIVATE
    lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OSspecific
    Pstream_dummy
    OpenFOAM

    finiteVolume
#    FLEX::fl
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=libNULL.so
)

target_link_options(${target_name} PRIVATE
    -Xlinker --add-needed
)

set(FOAM_regular_executables "${FOAM_regular_executables};${target_name}" PARENT_SCOPE)

add_library(Pstream_dummy SHARED
    UPstream.C
    UIPread.C
    UOPwrite.C
)

target_compile_definitions(Pstream_dummy PRIVATE
    LIB_NAME=libPstream.so
)

target_include_directories(Pstream_dummy PUBLIC
    lnInclude
    ${OpenFOAM_lnInclude_dir}
    "${CMAKE_SOURCE_DIR}/src/OSspecific/POSIX/lnInclude"
)
set_target_properties(Pstream_dummy
    PROPERTIES
    OUTPUT_NAME Pstream
)
target_link_libraries(Pstream_dummy PUBLIC
    OpenFOAM_Defines
    pthread
)

install(TARGETS Pstream_dummy
    DESTINATION lib/dummy
)
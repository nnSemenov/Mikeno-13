
add_library(Pstream_dummy SHARED
    UPstream.C
    UIPread.C
    UOPwrite.C
)

target_include_directories(Pstream_dummy PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/lnInclude
    ${OpenFOAM_lnInclude_dir}
)
set_target_properties(Pstream_dummy
    PROPERTIES
    OUTPUT_NAME Pstream
)
target_link_libraries(Pstream_dummy PUBLIC
    OpenFOAM_Defines
)

install(TARGETS Pstream_dummy
    DESTINATION lib/dummy
)

lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

add_library(Pstream_dummy SHARED
    UPstream.C
    UIPread.C
    UOPwrite.C
)

target_compile_definitions(Pstream_dummy PRIVATE
    LIB_NAME=libPstream.so
)

target_include_directories(Pstream_dummy PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lnInclude>
    $<BUILD_INTERFACE:${LIB_SRC}/OSspecific/POSIX/lnInclude>

    $<INSTALL_INTERFACE:../../src/Pstream/dummy/lnInclude>
)

target_include_directories(Pstream_dummy PRIVATE
#    $<BUILD_INTERFACE:${LIB_SRC}/OSspecific/POSIX/lnInclude>
    $<BUILD_INTERFACE:${LIB_SRC}/OpenFOAM/lnInclude>
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
    EXPORT MikenoTargets
    DESTINATION lib/dummy
)

set(FOAM_special_libraries "${FOAM_special_libraries};Pstream_dummy" PARENT_SCOPE)
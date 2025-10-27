
lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

add_library(Pstream_mpi SHARED
    UOPwrite.C
    UIPread.C
    UPstream.C
    PstreamGlobals.C
)

target_compile_definitions(Pstream_mpi PRIVATE
    LIB_NAME=libPstream.so
)

target_include_directories(Pstream_mpi PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lnInclude>
    $<BUILD_INTERFACE:${OpenFOAM_lnInclude_dir}>
    $<BUILD_INTERFACE:${LIB_SRC}/OSspecific/POSIX/lnInclude>
)
set_target_properties(Pstream_mpi
    PROPERTIES
    OUTPUT_NAME Pstream
)
target_link_libraries(Pstream_mpi PRIVATE
    OpenFOAM_Defines
    MPI::MPI_CXX
)

install(TARGETS Pstream_mpi
    EXPORT MikenoTargets
    DESTINATION lib/${FOAM_MPI}
)


set(FOAM_special_libraries "${FOAM_special_libraries};Pstream_mpi" PARENT_SCOPE)

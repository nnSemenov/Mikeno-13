
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
    lnInclude
    ${OpenFOAM_lnInclude_dir}
    "${CMAKE_SOURCE_DIR}/src/OSspecific/POSIX/lnInclude"
)
set_target_properties(Pstream_mpi
    PROPERTIES
    OUTPUT_NAME Pstream
)
target_link_libraries(Pstream_mpi PUBLIC
    OpenFOAM_Defines
    MPI::MPI_CXX
)

install(TARGETS Pstream_mpi
    DESTINATION lib/${FOAM_MPI}
)
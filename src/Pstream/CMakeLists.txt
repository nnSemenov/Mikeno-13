

add_subdirectory(dummy)
add_subdirectory(mpi)

add_library(Pstream_best ALIAS Pstream_mpi)

set(FOAM_special_libraries ${FOAM_special_libraries} PARENT_SCOPE)
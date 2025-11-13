file(GLOB config_files "${CMAKE_CURRENT_LIST_DIR}/3rdParty/*.cmake")

# Use extra number to ensure order. MPI must be configured before ptscotch
list(SORT config_files COMPARE FILE_BASENAME)

foreach (config_file ${config_files})
    include(${config_file})
#    cmake_path(GET config_file FILENAME fn)
#    message(${fn})
endforeach ()


# Add fake target for ptscotch. When finding package, ptscotch must link to MPI::MPI_C
if(NOT TARGET MPI::MPI_C)
    add_library(MPI::MPI_C ALIAS MPI::MPI_CXX)
endif ()
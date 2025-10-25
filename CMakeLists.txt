cmake_minimum_required(VERSION 3.28)
project(Mikeno VERSION 13 LANGUAGES CXX)

set(WM_PRECISION_OPTION DP CACHE STRING "Precision of float point number. SP | DP")

set(WM_LABEL_SIZE 32 CACHE STRING "Size of label. 32 | 64")

set(WM_MPLIB SYSTEMOPENMPI CACHE STRING "MPI implementation. SYSTEMOPENMPI | OPENMPI | SYSTEMMPI | MPICH
    | MPICH-GM | HPMPI | MPI | FJMPI | QSMPI | SGIMPI | INTELMPI")

set(WM_ARCH linux64 CACHE STRING "Computer arch")
set(WM_ARCH_OPTION 64 CACHE STRING "Computer arch option")

include(cmake/process_options.cmake)

include(cmake/3rdParty/zlib.cmake)
include(cmake/3rdParty/MPI.cmake)

include(cmake/lnInclude.cmake)


add_subdirectory(src)
cmake_minimum_required(VERSION 3.28)
project(Mikeno VERSION 13 LANGUAGES CXX)

set(WM_PRECISION_OPTION DP CACHE STRING "Precision of float point number. SP | DP")

set(WM_LABEL_SIZE 32 CACHE STRING "Size of label. 32 | 64")

set(WM_MPLIB SYSTEMOPENMPI CACHE STRING "MPI implementation. SYSTEMOPENMPI | OPENMPI | SYSTEMMPI | MPICH
    | MPICH-GM | HPMPI | MPI | FJMPI | QSMPI | SGIMPI | INTELMPI")

set(WM_ARCH linux64 CACHE STRING "Computer arch")
set(WM_ARCH_OPTION 64 CACHE STRING "Computer arch option")


#- Decomposition libraries:
#    <library>_TYPE = none | system | ThirdParty (OpenFOAM)
set(SCOTCH_TYPE system CACHE STRING "Scotch type")
set(METIS_TYPE system CACHE STRING "")
set(PARMETIS_TYPE system CACHE STRING "")
set(ZOLTAN_TYPE system CACHE STRING "")

#    ParaView_TYPE = none | system | paraviewopenfoam | ThirdParty (OpenFOAM)
set(ParaView_TYPE system CACHE STRING "")

#- Floating-point signal handling:
#    set or unset
#export FOAM_SIGFPE=

#- Memory initialisation:
#    set or unset
#export FOAM_SETNAN=


include(cmake/process_options.cmake)

include(cmake/3rdParty/zlib.cmake)
include(cmake/3rdParty/MPI.cmake)
include(cmake/3rdParty/metis.cmake)

include(cmake/lnInclude.cmake)



add_subdirectory(src)
cmake_minimum_required(VERSION 3.28)
project(Mikeno VERSION 13 LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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


include(cmake/3rdParty.cmake)

include(cmake/process_options.cmake)


include(cmake/lnInclude.cmake)

# libraries that are installed to lib.
set(FOAM_regular_libraries)
# libraries that don't install to lib, but different destination
set(FOAM_special_libraries)

add_subdirectory(src)


message(STATUS "Regular libraries: ${FOAM_regular_libraries}")
message(STATUS "Non-regular libraries: ${FOAM_special_libraries}")

install(TARGETS ${FOAM_regular_libraries}
    DESTINATION lib
)
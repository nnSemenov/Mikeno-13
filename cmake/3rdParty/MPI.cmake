#message(WARNING "WM_MPLIB is not actually supported yet. Simply find a MPI")

find_package(MPI REQUIRED)

message(STATUS "MPI_VERSION = ${MPI_VERSION}")

#set(MPILIB_SUPPORTED_LIST
#    SYSTEMMPI
#    MPICH
#)
#set(FOAM_MPI_LIST
#    mpi-system
#)

if(${WM_MPLIB} STREQUAL "SYSTEMOPENMPI")
    set(FOAM_MPI openmpi-system CACHE STRING "")
elseif (${WM_MPLIB} STREQUAL OPENMPI)
    set(FOAM_MPI "openmpi-${MPI_VERSION}" CACHE STRING "")
elseif (${WM_MPLIB} STREQUAL SYSTEMMPI)
    set(FOAM_MPI "mpi-system" CACHE STRING "")
else ()
    message(FATAL_ERROR "WM_MPLIB = ${WM_MPLIB} is not currently supported.")
endif ()

message(STATUS "FOAM_MPI = ${FOAM_MPI}")
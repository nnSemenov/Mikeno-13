if(${ParaView_TYPE} STREQUAL "none")
    message(STATUS "Skip finding openfoam because ParaView_TYPE = ${ParaView_TYPE}")
    return()
endif ()


find_package(ParaView CONFIG REQUIRED)
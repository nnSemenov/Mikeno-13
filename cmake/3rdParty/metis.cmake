if((NOT METIS_TYPE) OR (${METIS_TYPE} STREQUAL none))
    message(STATUS "Skip finding metis because METIS_TYPE = ${METIS_TYPE}")
    return()
endif ()

if(${WM_PRECISION_OPTION} STREQUAL SP)
    set(fp_size 32)
else ()
    set(fp_size 64)
endif ()

set(metis_option metis_Int${WM_LABEL_SIZE}_Real${fp_size})

message(STATUS "metis_option = ${metis_option}")

find_library(metis_lib
    NAMES ${metis_option} metis
)

if(NOT metis_lib)
    message(FATAL_ERROR "Failed to find metis library: ${metis_option}")
    return()
endif ()
message(STATUS "Found metis library: ${metis_lib}")

find_file(metis_header NAMES metis.h
    PATH_SUFFIXES ${metis_option}/include
#    NO_DEFAULT_PATH
)
if(NOT metis_header)
    message(WARNING "Failed to find metis header: ${metis_option}/include/metis.h")
    return()
endif ()
message(STATUS "Found metis header: ${metis_header}")
cmake_path(GET metis_header PARENT_PATH metis_include_dir)

add_library(metis_imported INTERFACE)
target_include_directories(metis_imported INTERFACE ${metis_include_dir})
target_link_libraries(metis_imported INTERFACE ${metis_lib})


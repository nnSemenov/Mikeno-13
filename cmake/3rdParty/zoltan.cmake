if((NOT ZOLTAN_TYPE) OR (${ZOLTAN_TYPE} STREQUAL none))
    message(STATUS "Skip finding zoltan because ZOLTAN_TYPE = ${ZOLTAN_TYPE}")
    return()
endif ()

find_library(zoltan_lib
    NAMES zoltan
)
if(NOT zoltan_lib)
    message(WARNING "Failed to find zoltan lib")
    return()
endif ()
message(STATUS "Found zoltan lib ${zoltan_lib}")

find_file(zoltan_header
    NAMES zoltan.h
)
if(NOT zoltan_header)
    message(WARNING "Failed to find zoltan header")
    return()
endif ()
message(STATUS "Found zoltan header ${zoltan_header}")
cmake_path(GET zoltan_header PARENT_PATH zoltan_include_dir)

add_library(zoltan_imported INTERFACE)
target_link_libraries(zoltan_imported INTERFACE ${zoltan_lib})
target_include_directories(zoltan_imported INTERFACE ${zoltan_include_dir})
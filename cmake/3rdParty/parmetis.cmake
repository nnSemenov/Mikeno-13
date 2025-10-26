if((NOT PARMETIS_TYPE) OR (${PARMETIS_TYPE} STREQUAL none))
    message(STATUS "Skip finding metis because PARMETIS_TYPE = ${PARMETIS_TYPE}")
    return()
endif ()

find_library(parmetis_lib
    NAMES parmetis
)
if(NOT parmetis_lib)
    message(WARNING "Failed to find parmteis lib")
    return()
endif ()
message(STATUS "Found parmetis library: ${parmetis_lib}")

find_file(parmetis_header
    NAMES parmetis.h
)
if(NOT parmetis_header)
    message(WARNING "Failed to find parmteis header")
    return()
endif ()
message(STATUS "Found parmetis header ${parmetis_header}")
cmake_path(GET parmetis_header PARENT_PATH parmetis_include_dir)

add_library(parmetis_imported INTERFACE)
target_link_libraries(parmetis_imported INTERFACE ${parmetis_lib})
target_include_directories(parmetis_imported INTERFACE ${parmetis_include_dir})
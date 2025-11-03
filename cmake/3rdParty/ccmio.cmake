
set(txt "Some optional utilities may be skipped.")

find_library(ccmio_lib
    NAMES ccmio
)
if(NOT ${ccmio_lib})
    message(STATUS "libccmio not found. ${txt}")
    return()
endif ()
message(STATUS "Found ccmio library: ${ccmio_lib}")

find_file(ccmio_header
    NAMES ccmio.h
)
if(NOT ${ccmio_header})
    message(STATUS "ccmio.h not found. ${txt}")
    return()
endif ()
message(STATUS "Found ccmio header ${ccmio_header}")

cmake_path(GET ccmio_header PARENT_PATH ccmio_include_dir)

add_library(ccmio_imported INTERFACE)
target_link_libraries(ccmio_imported INTERFACE ${ccmio_lib})
target_include_directories(ccmio_imported INTERFACE ${ccmio_include_dir})
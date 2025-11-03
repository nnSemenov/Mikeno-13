find_library(tecio_lib
    NAMES tecio
)

find_file(tecio_header
    NAMES TECIO.h
)

set(txt "Some optional utilities may be skipped.")

if(NOT ${tecio_lib})
    message(STATUS "Failed to find tecio library. ${txt}")
    return()
endif ()

if(NOT ${tecio_header})
    message(STATUS "Failed to find tecio header. ${txt}")
    return()
endif ()

cmake_path(GET tecio_header PARENT_PATH tecio_include_dir)

add_library(tecio_imported INTERFACE)
target_link_libraries(tecio_imported INTERFACE ${tecio_lib})
target_include_directories(tecio_imported INTERFACE ${tecio_include_dir})
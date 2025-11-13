find_library(MGridGen_lib
    NAMES MGridGen
)

if(NOT MGridGen_lib)
    message(STATUS "MGridGen library not found.")
    return()
endif ()
message(STATUS "Found MGridGen library: ${MGridGen_lib}")

find_file(MGridGen_header
    NAMES mgridgen.h
)
if(NOT MGridGen_header)
    message(STATUS "MGridGen header not found.")
    return()
endif ()
message(STATUS "Found MGridGen header: ${MGridGen_header}")

cmake_path(GET MGridGen_header PARENT_PATH MGridGen_include_dir)

add_library(MGridGen_imported INTERFACE)
target_link_libraries(MGridGen_imported INTERFACE ${MGridGen_lib})
target_include_directories(MGridGen_imported INTERFACE ${MGridGen_include_dir})
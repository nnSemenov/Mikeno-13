find_file(rapidcsv_header
    NAMES rapidcsv.h
)

if(EXISTS ${rapidcsv_header})
    message(STATUS "Found rapidcsv header: ${rapidcsv_header}")
    cmake_path(GET rapidcsv_header PARENT_PATH rapidcsv_include)

    add_library(rapidcsv INTERFACE)
    target_include_directories(rapidcsv INTERFACE ${rapidcsv_include})

    return()
endif ()

include(FetchContent)
message(STATUS "Downloading rapidcsv...")
FetchContent_Declare(rapidcsv
    GIT_REPOSITORY https://github.com/d99kris/rapidcsv.git
    GIT_TAG v8.90
    OVERRIDE_FIND_PACKAGE
)

FetchContent_MakeAvailable(rapidcsv)

find_package(rapidcsv REQUIRED)

if(NOT TARGET rapidcsv)
    message(FATAL_ERROR "Package rapidcsv is found, but target rapidcsv is not found.")
endif ()
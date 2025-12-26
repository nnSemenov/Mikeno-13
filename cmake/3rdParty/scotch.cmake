
set(SCOTCH_OK OFF)
set(PTSCOTCH_OK OFF)

if ((NOT SCOTCH_TYPE) OR (${SCOTCH_TYPE} STREQUAL none))
    message(STATUS "Skip finding scotch because SCOTCH_TYPE = ${SCOTCH_TYPE}")
    return()
endif ()

find_package(SCOTCH CONFIG)
if(NOT SCOTCH_FOUND)
    message(STATUS "find_package failed to find scotch. Search it manually...")
    include(${CMAKE_SOURCE_DIR}/cmake/3rdParty/fallback/scotch.cmake)
    return()
endif()

set(expected_targets SCOTCH::scotch SCOTCH::scotcherr)
foreach (target ${expected_targets})
    if (NOT TARGET ${target})
        message(FATAL_ERROR "Target ${target} is missing")
        return()
    endif ()
endforeach ()

set(SCOTCH_OK ON)

if(NOT TARGET SCOTCH::ptscotch)
    message(WARNING "SCOTCH::ptscotch is missing")
    return()
endif ()
set(PTSCOTCH_OK OFF)
#message(STATUS "Found real time lib: ${real_time_lib}")

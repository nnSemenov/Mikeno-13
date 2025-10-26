
set(SCOTCH_OK OFF)

if ((NOT SCOTCH_TYPE) OR (${SCOTCH_TYPE} STREQUAL none))
    message(STATUS "Skip finding scotch because SCOTCH_TYPE = ${SCOTCH_TYPE}")
    return()
endif ()


find_package(SCOTCH CONFIG)
set(expected_targets SCOTCH::scotch SCOTCH::scotcherr)
foreach (target ${expected_targets})
    if (NOT TARGET ${target})
        message(WARNING "Target ${target} is missing")
        return()
    endif ()
endforeach ()

find_library(real_time_lib NAMES rt)
if(NOT real_time_lib)
    message(WARNING "real time lib (like librt.so) is missing.")
    return()
endif ()

set(SCOTCH_OK ON)

#message(STATUS "Found real time lib: ${real_time_lib}")
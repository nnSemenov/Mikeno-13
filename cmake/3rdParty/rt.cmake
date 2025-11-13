set(real_time_OK OFF)

find_library(real_time_lib NAMES rt)
if(NOT real_time_lib)
    message(WARNING "real time lib (like librt.so) is missing.")
    return()
endif ()

set(real_time_OK ON)
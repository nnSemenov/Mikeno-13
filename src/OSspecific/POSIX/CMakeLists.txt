
lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

add_library(OSspecific OBJECT
    signals/sigFpe.C
    signals/sigSegv.C
    signals/sigInt.C
    signals/sigQuit.C
    signals/sigStopAtWriteNow.C
    signals/sigWriteNow.C
    regExp.C
    timer.C
    fileStat.C
    POSIX.C
    cpuTime/cpuTime.C
    clockTime/clockTime.C
    memInfo/memInfo.C
    # Note: fileMonitor assumes inotify by default. Compile with -DFOAM_USE_STAT
    # to use stat (=timestamps) instead of inotify
    fileMonitor.C
)

if(${WM_ARCH} STREQUAL "SunOS64")
    target_sources(OSspecific PRIVATE
        dummyPrintStack.C
    )
else()
    target_sources(OSspecific PRIVATE
        printStack.C
    )
endif ()


target_compile_definitions(OSspecific PRIVATE
    LIB_NAME=libOSspecific.o
)

if(EXISTS "/usr/include/sys/inotify.h")
    target_compile_definitions(OSspecific PRIVATE FOAM_USE_INOTIFY)
endif()

target_compile_options(OSspecific PRIVATE -fPIC)

target_link_libraries(OSspecific PUBLIC
    OpenFOAM_Defines
)

target_include_directories(OSspecific PUBLIC
    ${OpenFOAM_lnInclude_dir}
    lnInclude
)

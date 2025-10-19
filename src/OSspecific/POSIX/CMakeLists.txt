
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

if(EXISTS "/usr/include/sys/inotify.h")
    target_compile_definitions(OSspecific PUBLIC FOAM_USE_INOTIFY)
endif()

target_link_libraries(OSspecific PUBLIC
    OpenFOAM_Defines
)

target_include_directories(OSspecific PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
    ${OpenFOAM_lnInclude_dir}
)

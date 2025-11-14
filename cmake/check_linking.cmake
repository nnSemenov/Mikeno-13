

set(linking_tool "ldd" CACHE STRING "Tool for link examination")
set(search_dirs "" CACHE PATH "Directories to be searched")

function(try_linking exe_loc working_dir)
    execute_process(
        COMMAND ${linking_tool} -r -d ${exe_loc}
        WORKING_DIRECTORY ${working_dir}
        OUTPUT_VARIABLE output
    )

    if((${output} MATCHES "not found") OR (${output} MATCHES "undefined symbol"))
        message(FATAL_ERROR "${exe_loc} failed to be loaded: \n${output}")
    endif ()
endfunction()

foreach (dir ${search_dirs})
    message(STATUS "Checking all executable / libraries under ${dir}")
    file(GLOB_RECURSE exe_libs LIST_DIRECTORIES false "${dir}/*")

    set(dylib_only ON)
    cmake_path(GET dir FILENAME stem)
    if(${stem} STREQUAL "bin")
        set(dylib_only OFF)
    endif ()

    foreach (exe ${exe_libs})
        cmake_path(GET exe EXTENSION exe_extension)

        if(exe_extension STREQUAL ".sh")
            continue()
        endif ()

        # Check if this file should be skipped
        if(${dylib_only}) # lib
            if(NOT ${exe_extension} MATCHES ".so")
                continue()
            endif ()
        else ()
        endif ()

        message(STATUS "Checking ${exe} ...")
        try_linking(${exe} ${dir})

    endforeach ()
endforeach ()
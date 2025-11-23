function(check_if_AOCC OUT_VAR)

    set(${OUT_VAR} OFF PARENT_SCOPE)

    if(NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
        # Not some kind of clang
        return()
    endif ()

    execute_process(COMMAND ${CMAKE_CXX_COMPILER} --version
        OUTPUT_VARIABLE clang_output
        OUTPUT_STRIP_TRAILING_WHITESPACE
        COMMAND_ERROR_IS_FATAL ANY
    )
    string(REPLACE "\n" ";" clang_output ${clang_output})
    list(GET clang_output 0 first_line)
    if(${first_line} MATCHES "AMD clang")
        set(${OUT_VAR} ON PARENT_SCOPE)
        return()
    endif ()

    if(${first_line} MATCHES "AOCC")
        set(${OUT_VAR} ON PARENT_SCOPE)
        return()
    endif ()
endfunction()
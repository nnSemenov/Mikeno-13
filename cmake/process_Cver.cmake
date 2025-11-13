

function(process_Cver source dest)
    set(VERSION_STRING ${PROJECT_VERSION})
    set(BUILD_STRING "CMakeBuild")
    configure_file(${source} ${dest})
endfunction()
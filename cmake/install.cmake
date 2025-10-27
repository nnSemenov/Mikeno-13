
list(LENGTH FOAM_regular_libraries N_regular_lib)
list(LENGTH FOAM_special_libraries N_special_lib)
message(STATUS "${N_regular_lib} regular libraries: ${FOAM_regular_libraries}")
message(STATUS "${N_special_lib} non-regular libraries: ${FOAM_special_libraries}")

foreach (target ${FOAM_regular_libraries})
    get_target_property(interface_include_dirs ${target} INTERFACE_INCLUDE_DIRECTORIES)
    #    if(NOT interface_include_dirs)
    #        continue()
    #    endif ()
    #    message("${target} interfacely include ${interface_include_dirs}")
    set(new_include_dirs "")
    foreach (dir ${interface_include_dirs})
        if (${dir} MATCHES "$<:*>")
            list(APPEND new_include_dirs ${dir})
            continue()
        endif ()
        list(APPEND new_include_dirs "$<BUILD_INTERFACE:${dir}>")
    endforeach ()
    #    message("new_include_dirs = ${new_include_dirs}")
    set_target_properties(${target} PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${new_include_dirs}"
    )
endforeach ()

install(TARGETS ${FOAM_regular_libraries}
    EXPORT MikenoTargets
    DESTINATION lib
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ             GROUP_EXECUTE
    WORLD_READ             WORLD_EXECUTE
)


install(EXPORT MikenoTargets
    DESTINATION lib/cmake
    NAMESPACE Mikeno::
)

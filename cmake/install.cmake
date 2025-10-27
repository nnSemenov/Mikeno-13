
list(LENGTH FOAM_regular_libraries N_regular_lib)
list(LENGTH FOAM_special_libraries N_special_lib)
message(STATUS "${N_regular_lib} regular libraries: ${FOAM_regular_libraries}")
message(STATUS "${N_special_lib} non-regular libraries: ${FOAM_special_libraries}")

# Convert all absolute path into $<> expression
foreach (target ${FOAM_regular_libraries})
    get_target_property(interface_include_dirs ${target} INTERFACE_INCLUDE_DIRECTORIES)
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
    PERMISSIONS OWNER_READ OWNER_EXECUTE OWNER_WRITE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${CMAKE_BINARY_DIR}/MikenoConfig.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(FILES "${CMAKE_BINARY_DIR}/MikenoConfig.cmake"
    DESTINATION lib/cmake
)

install(EXPORT MikenoTargets
    DESTINATION lib/cmake
    NAMESPACE Mikeno::
)

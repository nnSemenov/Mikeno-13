
list(LENGTH FOAM_regular_libraries N_regular_lib)
list(LENGTH FOAM_special_libraries N_special_lib)
list(LENGTH FOAM_regular_executables N_regular_exe)
message(STATUS "${N_regular_lib} regular libraries: ${FOAM_regular_libraries}")
message(STATUS "${N_special_lib} non-regular libraries: ${FOAM_special_libraries}")
message(STATUS "${N_regular_exe} regular executables: ${FOAM_regular_executables}")

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
        cmake_path(IS_PREFIX WM_PROJECT_DIR ${dir} NORMALIZE is_prefix)
        if(${is_prefix})
        cmake_path(RELATIVE_PATH dir BASE_DIRECTORY ${WM_PROJECT_DIR} OUTPUT_VARIABLE relative_dir)
            set(inc_dir_str "$<INSTALL_INTERFACE:../../${relative_dir}>")
            list(APPEND new_include_dirs ${inc_dir_str})
            # message("\t ${dir} -> ${inc_dir_str}")
        endif()
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

install(TARGETS ${FOAM_regular_executables}
    EXPORT MikenoTargets
    DESTINATION bin
    PERMISSIONS OWNER_READ OWNER_EXECUTE OWNER_WRITE
                GROUP_READ GROUP_EXECUTE
                WORLD_READ WORLD_EXECUTE
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/MikenoConfig.cmake.in
    ${CMAKE_BINARY_DIR}/MikenoConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX}
    PATH_VARS FOAM_regular_libraries FOAM_special_libraries FOAM_regular_executables
)

write_basic_package_version_file(${CMAKE_BINARY_DIR}/MikenoConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(FILES 
    ${CMAKE_BINARY_DIR}/MikenoConfigVersion.cmake
    ${CMAKE_BINARY_DIR}/MikenoConfig.cmake
    DESTINATION lib/cmake/Mikeno
)

install(EXPORT MikenoTargets
    FILE MikenoTargets.cmake
    DESTINATION lib/cmake/Mikeno
    NAMESPACE Mikeno::
)

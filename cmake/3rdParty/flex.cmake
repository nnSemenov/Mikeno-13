find_package(FLEX REQUIRED)

message(STATUS "Found Flex: ${FLEX_EXECUTABLE}")

if(${FLEX_FOUND} AND NOT TARGET FLEX::fl)
    add_library(FLEX::fl INTERFACE IMPORTED)
    set_target_properties(
        FLEX::fl
        PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${FLEX_INCLUDE_DIRS}"
        INTERFACE_LINK_LIBRARIES "${FLEX_LIBRARIES}"
    )
endif()


#function(flex_process_file source dest)
#    execute_process(
#        COMMAND ${FLEX_EXECUTABLE} -o ${dest} ${source}
#        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#
#        COMMAND_ERROR_IS_FATAL ANY
#    )
#endfunction()
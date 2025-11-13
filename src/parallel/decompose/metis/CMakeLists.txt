set(target_name metisDecomp)

if(NOT TARGET metis_imported)
    message(STATUS "Skip ${target_name} because metis not found")
    return()
endif ()

lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

add_library(${target_name} SHARED
    metis.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_include_directories(${target_name} PRIVATE
    ../decompositionMethods/lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    metis_imported
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



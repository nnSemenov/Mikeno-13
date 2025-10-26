set(target_name zoltanDecomp)

if(NOT TARGET zoltan_imported)
    message(STATUS "Skip ${target_name} because zoltan not found")
    return()
endif ()

lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

add_library(${target_name} SHARED
    zoltan.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_include_directories(${target_name} PRIVATE
    ../decompositionMethods/lnInclude
    ${LIB_SRC}/Pstream/mpi/lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    zoltan_imported
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



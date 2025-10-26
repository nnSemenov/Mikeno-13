set(target_name scotchDecomp)

if(NOT ${SCOTCH_OK})
    message(STATUS "Skip ${target_name} because SCOTCH_OK = ${SCOTCH_OK}")
    return()
endif ()


lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

add_library(${target_name} SHARED
    scotch.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_include_directories(${target_name} PRIVATE
    ../decompositionMethods/lnInclude
)

message(STATUS "real_time_lib = ${real_time_lib}")

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    SCOTCH::scotch
    SCOTCH::scotcherr
    ${real_time_lib}
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



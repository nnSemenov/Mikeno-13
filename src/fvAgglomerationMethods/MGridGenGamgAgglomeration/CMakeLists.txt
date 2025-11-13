if(NOT TARGET MGridGen_imported)
    message(STATUS "MGridGen library is not found, skip MGridGenGAMGAgglomeration.")
    return()
endif ()

message(WARNING "Support for MGridGenGAMGAgglomeration haven't been tested, may fail.")

lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name MGridGenGAMGAgglomeration)

add_library(${target_name} SHARED
    MGridGenGAMGAgglomeration.C
    MGridGenGAMGAgglomerate.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_include_directories(${target_name} PRIVATE
    ${LIB_SRC}/finiteVolume/lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    MGridGen_imported
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

if(NOT ${WM_PRECISION_OPTION} STREQUAL "SP")
    target_compile_definitions(${target_name} PRIVATE
        TYPE_REAL
    )
endif ()

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



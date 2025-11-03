if(NOT TARGET ccmio_imported)
    message(STATUS "ccm26ToFoam is skipped because we don't find ccmio library, which is proprietary")
    return()
endif()


lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name ccm26ToFoam)

add_executable(${target_name}
    ccm26ToFoam.C
)

target_include_directories(${target_name} PRIVATE
    lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OSspecific
    OpenFOAM
    
    Pstream_best
    finiteVolume
    meshTools
    ccmio_imported
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=libNULL.so
)

set(FOAM_regular_executables "${FOAM_regular_executables};${target_name}" PARENT_SCOPE)
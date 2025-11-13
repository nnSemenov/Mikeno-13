if(NOT TARGET tecio_imported)
    message(STATUS "foamToTecplot360 is skipped because tecio is not found.")
    return()
endif ()

lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name foamToTecplot360)

add_executable(${target_name}
    tecplotWriter.C
    foamToTecplot360.C
)

target_include_directories(${target_name} PRIVATE
    lnInclude
    ${LIB_SRC}/tracking/lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OSspecific
    OpenFOAM

    foamToVTK
    lagrangian
    polyTopoChange
    genericFvFields
    Pstream_best

    tecio_imported
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=libNULL.so
)

set(FOAM_regular_executables "${FOAM_regular_executables};${target_name}" PARENT_SCOPE)
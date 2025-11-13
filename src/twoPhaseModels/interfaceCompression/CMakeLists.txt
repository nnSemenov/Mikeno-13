lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name interfaceCompression)

add_library(${target_name} SHARED
    interfaceCompression/interfaceCompression.C
    noInterfaceCompression/noInterfaceCompression.C

    MPLIC/MPLICface.C
    MPLIC/MPLICcellStorage.C
    MPLIC/MPLICcell.C
    MPLIC/MPLIC.C
    MPLIC/MPLICU.C

    PLIC/PLIC.C
    PLIC/PLICU.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
    ${LIB_SRC}/physicalProperties/lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    finiteVolume
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

add_library(solidThermo SHARED
    solidThermo/solidThermo.C
    solidThermo/solidThermos.C
    constSolidThermo/constSolidThermo.C
    constAnisoSolidThermo/constAnisoSolidThermo.C
)
target_include_directories(solidThermo PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_include_directories(solidThermo PRIVATE
    ${LIB_SRC}/physicalProperties/lnInclude
)

target_compile_options(solidThermo PRIVATE
    -ffp-exception-behavior=maytrap
)

target_link_libraries(solidThermo PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    meshTools 
    finiteVolume 
    specie 
    fluidThermophysicalModels 
    multicomponentThermophysicalModels
)

target_compile_definitions(solidThermo PRIVATE
    LIB_NAME=libsolidThermo.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};solidThermo" PARENT_SCOPE)



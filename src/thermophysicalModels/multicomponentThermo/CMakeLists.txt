lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

add_library(multicomponentThermophysicalModels SHARED
    multicomponentThermo/multicomponentThermo.C

    fluidMulticomponentThermo/fluidMulticomponentThermo.C

    psiMulticomponentThermo/psiMulticomponentThermo.C
    psiMulticomponentThermo/psiMulticomponentThermos.C

    rhoFluidMulticomponentThermo/rhoFluidMulticomponentThermo.C
    rhoFluidMulticomponentThermo/rhoFluidMulticomponentThermos.C

    functionObjects/moleFractions/moleFractions.C
    functionObjects/massFractions/massFractions.C
)

target_include_directories(multicomponentThermophysicalModels PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_include_directories(multicomponentThermophysicalModels PRIVATE
    "${LIB_SRC}/physicalProperties/lnInclude"
)

target_link_libraries(multicomponentThermophysicalModels PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    fluidThermophysicalModels
    specie
    finiteVolume
    Pstream_best
)

target_compile_definitions(multicomponentThermophysicalModels PRIVATE
    LIB_NAME=libmulticomponentThermophysicalModels.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};multicomponentThermophysicalModels" PARENT_SCOPE)



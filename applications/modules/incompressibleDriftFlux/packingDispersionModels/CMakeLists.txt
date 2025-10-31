lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name incompressibleDriftFluxPackingDispersionModels)

add_library(${target_name} SHARED
    packingDispersionModel/packingDispersionModel.C
    none/none_packingDispersionModel.C
    DeClercq/DeClercq.C
    Green/Green.C
    Landman/Landman.C
    Usher/Usher.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_include_directories(${target_name} PRIVATE
    ../incompressibleDriftFluxMixture
    ../mixtureViscosityModels/lnInclude
    ../relativeVelocityModels/lnInclude

    ${FOAM_MODULES}/twoPhaseSolver/lnInclude
    ${FOAM_MODULES}/VoFSolver/lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    incompressibleDriftFluxRelativeVelocityModels
    physicalProperties
    twoPhaseMixture
    incompressibleTwoPhases
    finiteVolume
    meshTools
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



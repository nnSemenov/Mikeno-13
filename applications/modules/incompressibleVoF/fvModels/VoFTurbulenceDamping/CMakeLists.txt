lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name VoFTurbulenceDamping)

add_library(${target_name} SHARED
    VoFTurbulenceDamping.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_include_directories(${target_name} PRIVATE
    ${FOAM_MODULES}/twoPhaseVoFSolver/lnInclude
    ${FOAM_MODULES}/twoPhaseSolver/lnInclude
    ${FOAM_MODULES}/VoFSolver/lnInclude
    ${FOAM_MODULES}/incompressibleVoF/lnInclude
    ${LIB_SRC}/physicalProperties/lnInclude
    ${LIB_SRC}/twoPhaseModels/twoPhaseMixture/lnInclude
    ${LIB_SRC}/twoPhaseModels/incompressibleTwoPhases/lnInclude
    ${LIB_SRC}/MomentumTransportModels/momentumTransportModels/lnInclude
    ${LIB_SRC}/MomentumTransportModels/incompressible/lnInclude
    ${LIB_SRC}/finiteVolume/lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    incompressibleVoFSolver
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



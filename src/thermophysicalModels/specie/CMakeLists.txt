lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

add_library(specie SHARED
    atomicWeights/atomicWeights.C
    specie/specie.C
    reaction/specieCoeffs/specieCoeffs.C
    reaction/reaction/reaction.C

    equationOfState/cubicEOS.C

    thermophysicalFunctions/integratedNonUniformTable1/integratedNonUniformTable1.C
    thermophysicalFunctions/APIdiffCoef/APIdiffCoef.C
    thermophysicalFunctions/binaryDiffusionCoefficient/binaryDiffusionCoefficient.C
)

set(NSRDS thermophysicalFunctions/NSRDS)
target_sources(specie PRIVATE
    ${NSRDS}/NSRDS0/NSRDS0.C
    ${NSRDS}/NSRDS1/NSRDS1.C
    ${NSRDS}/NSRDS2/NSRDS2.C
    ${NSRDS}/NSRDS3/NSRDS3.C
    ${NSRDS}/NSRDS4/NSRDS4.C
    ${NSRDS}/NSRDS5/NSRDS5.C
    ${NSRDS}/NSRDS6/NSRDS6.C
    ${NSRDS}/NSRDS7/NSRDS7.C
    ${NSRDS}/NSRDS14/NSRDS14.C
)


target_include_directories(specie PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_link_libraries(specie PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific
)

install(TARGETS specie
    DESTINATION lib
)
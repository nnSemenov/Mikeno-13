lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name radiationModels)

add_library(${target_name} SHARED
    # Radiation model
    radiationModels/radiationModel/radiationModel.C
    radiationModels/radiationModel/radiationModelNew.C
    radiationModels/noRadiation/noRadiation.C
    radiationModels/P1/P1.C
    radiationModels/fvDOM/fvDOM.C
    radiationModels/fvDOM/radiativeIntensityRay/radiativeIntensityRay.C
    radiationModels/fvDOM/blackBodyEmission/blackBodyEmission.C
    radiationModels/fvDOM/absorptionCoeffs/absorptionCoeffs.C
    radiationModels/viewFactor/viewFactor.C
    radiationModels/opaqueSolid/opaqueSolid.C

    # Scatter model
    scatterModels/scatterModel/scatterModel.C
    scatterModels/scatterModel/scatterModelNew.C
    scatterModels/noScatter/noScatter.C
    scatterModels/constantScatter/constantScatter.C

    # Absorption/Emission model
    absorptionEmissionModels/absorptionEmissionModel/absorptionEmissionModel.C
    absorptionEmissionModels/absorptionEmissionModel/absorptionEmissionModelNew.C
    absorptionEmissionModels/noAbsorptionEmission/noAbsorptionEmission.C
    absorptionEmissionModels/constantAbsorptionEmission/constantAbsorptionEmission.C
    absorptionEmissionModels/binary/binary.C
    absorptionEmissionModels/greyMean/greyMean.C
    absorptionEmissionModels/wideBand/wideBand.C
    absorptionEmissionModels/interpolationLookUpTable/interpolationLookUpTable.C

    # Soot model
    sootModels/sootModel/sootModel.C
    sootModels/sootModel/sootModelNew.C
    sootModels/noSoot/noSoot.C

    # Boundary conditions
    derivedFvPatchFields/MarshakRadiation/MarshakRadiationFvPatchScalarField.C
    derivedFvPatchFields/MarshakRadiationFixedTemperature/MarshakRadiationFixedTemperatureFvPatchScalarField.C
    derivedFvPatchFields/greyDiffusiveRadiation/greyDiffusiveRadiationMixedFvPatchScalarField.C
    derivedFvPatchFields/wideBandDiffusiveRadiation/wideBandDiffusiveRadiationMixedFvPatchScalarField.C
    derivedFvPatchFields/radiationCoupledBase/radiationCoupledBase.C
    derivedFvPatchFields/greyDiffusiveViewFactor/greyDiffusiveViewFactorFixedValueFvPatchScalarField.C

    # fvModels
    fvModels/radiation/radiation.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_include_directories(${target_name} PRIVATE
    ${LIB_SRC}/physicalProperties/lnInclude
    ${LIB_SRC}/thermophysicalModels/multicomponentThermo/lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    fluidThermophysicalModels 
    specie 
    solidThermo 
    thermophysicalProperties 
    finiteVolume 
    meshTools
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



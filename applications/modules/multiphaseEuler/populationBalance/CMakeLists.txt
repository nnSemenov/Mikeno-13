lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name populationBalance)

add_library(${target_name} SHARED
    populationBalanceModel/populationBalanceModel.C

    diameterModels/velocityGroup/velocityGroup.C
)

set(sizeGroup diameterModels/velocityGroup/sizeGroup)
set(shapeModels ${sizeGroup}/shapeModels)

target_sources(${target_name} PRIVATE
    ${sizeGroup}/sizeGroup.C

    ${shapeModels}/shapeModel/shapeModel.C
    ${shapeModels}/spherical/spherical.C
    ${shapeModels}/fractal/fractal.C
)

target_sources(${target_name} PRIVATE
    coalescenceModels/coalescenceModel/coalescenceModel.C
    coalescenceModels/AdachiStuartFokkink/AdachiStuartFokkink.C
    coalescenceModels/ballisticCollisions/ballisticCollisions.C
    coalescenceModels/BrownianCollisions/BrownianCollisions.C
    coalescenceModels/constantCoalescence/constantCoalescence.C
    coalescenceModels/CoulaloglouTavlarides/CoulaloglouTavlarides.C
    coalescenceModels/DahnekeInterpolation/DahnekeInterpolation.C
    coalescenceModels/hydrodynamic/hydrodynamic.C
    coalescenceModels/LehrMilliesMewesCoalescence/LehrMilliesMewesCoalescence.C
    coalescenceModels/LiaoCoalescence/LiaoCoalescence.C
    coalescenceModels/Luo/Luo.C
    coalescenceModels/PrinceBlanch/PrinceBlanch.C
    coalescenceModels/turbulentShear/turbulentShear.C

    binaryBreakupModels/binaryBreakupModel/binaryBreakupModel.C
    binaryBreakupModels/LehrMilliesMewes/LehrMilliesMewes.C
    binaryBreakupModels/Liao/LiaoBase.C
    binaryBreakupModels/Liao/Liao.C
    binaryBreakupModels/LuoSvendsen/LuoSvendsen.C
    binaryBreakupModels/powerLawUniformBinary/powerLawUniformBinary.C

    breakupModels/breakupModel/breakupModel.C
    breakupModels/exponential/exponential.C
    breakupModels/Kusters/Kusters.C
    breakupModels/Laakkonen/Laakkonen.C
    breakupModels/powerLaw/powerLaw.C

    daughterSizeDistributionModels/daughterSizeDistributionModel/daughterSizeDistributionModel.C
    daughterSizeDistributionModels/LaakkonenDaughterSizeDistribution/LaakkonenDaughterSizeDistribution.C
    daughterSizeDistributionModels/uniformBinary/uniformBinary.C

    derivedFvPatchFields/singleSizeGroup/singleSizeGroupFvPatchScalarField.C
    derivedFvPatchFields/distributionSizeGroup/distributionSizeGroupFvPatchScalarField.C

    derivedFvFieldSources/growth/growthFvScalarFieldSource.C

    derivedFvFieldSources/singleSizeGroup/singleSizeGroupFvScalarFieldSource.C
    derivedFvFieldSources/distributionSizeGroup/distributionSizeGroupFvScalarFieldSource.C
    derivedFvFieldSources/growthSizeGroup/growthSizeGroupFvScalarFieldSource.C
    derivedFvFieldSources/interfacialGrowthSizeGroup/interfacialGrowthSizeGroupFvScalarFieldSource.C

    derivedFvFieldSources/secondaryProperty/secondaryPropertyFvScalarFieldSource.C
    derivedFvFieldSources/growthSecondaryProperty/growthSecondaryPropertyFvScalarFieldSource.C

    derivedFvFieldSources/uniformFixedValueSurfaceAreaVolumeRatio/uniformFixedValueSurfaceAreaVolumeRatioFvScalarFieldSource.C
    derivedFvFieldSources/interfacialGrowthSurfaceAreaVolumeRatio/interfacialGrowthSurfaceAreaVolumeRatioFvScalarFieldSource.C
    derivedFvFieldSources/hardSphereSurfaceAreaVolumeRatio/hardSphereSurfaceAreaVolumeRatioFvScalarFieldSource.C
    derivedFvFieldSources/ParkRogakSurfaceAreaVolumeRatio/ParkRogakSurfaceAreaVolumeRatioFvScalarFieldSource.C

    populationBalanceSystem/populationBalanceSystem.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_include_directories(${target_name} PRIVATE
    ${LIB_SRC}/meshTools/lnInclude
    ${LIB_SRC}/finiteVolume/lnInclude
    ${LIB_SRC}/sampling/lnInclude
    ${LIB_SRC}/physicalProperties/lnInclude
    ${LIB_SRC}/thermophysicalModels/basic/lnInclude
    ${LIB_SRC}/thermophysicalModels/specie/lnInclude
    ${LIB_SRC}/thermophysicalModels/multicomponentThermo/lnInclude
    ${LIB_SRC}/twoPhaseModels/twoPhaseMixture/lnInclude
    ${LIB_SRC}/twoPhaseModels/compressibleTwoPhases/lnInclude
    ${LIB_SRC}/MomentumTransportModels/momentumTransportModels/lnInclude
    ${LIB_SRC}/MomentumTransportModels/compressible/lnInclude
    ${LIB_SRC}/MomentumTransportModels/phaseCompressible/lnInclude
    ${LIB_SRC}/ThermophysicalTransportModels/thermophysicalTransportModel/lnInclude
    ${LIB_SRC}/ThermophysicalTransportModels/fluid/lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific
    phaseSystem
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



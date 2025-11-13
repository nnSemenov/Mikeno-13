lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name lagrangianParcel)

set(PARCELS parcels)
set(BASEPARCELS ${PARCELS}/baseClasses)
set(DERIVEDPARCELS ${PARCELS}/derived)

set(CLOUDS clouds)
set(BASECLOUDS ${CLOUDS}/baseClasses)
set(DERIVEDCLOUDS ${CLOUDS}/derived)

add_library(${target_name} SHARED

    # Thermo
    parcelThermo/parcelThermo.C

    # parcel cloud
    parcelCloud/parcelCloudBase.C
    parcelCloud/parcelCloud.C
    parcelCloud/parcelCloudNew.C
    parcelCloud/parcelCloudList.C
    parcelCloud/parcelClouds.C

    # cloud names
    ${CLOUDS}/Templates/MomentumCloud/MomentumCloudName.C
    ${CLOUDS}/Templates/CollidingCloud/CollidingCloudName.C
    ${CLOUDS}/Templates/MPPICCloud/MPPICCloudName.C
    ${CLOUDS}/Templates/ThermoCloud/ThermoCloudName.C
    ${CLOUDS}/Templates/ReactingCloud/ReactingCloudName.C
    ${CLOUDS}/Templates/ReactingMultiphaseCloud/ReactingMultiphaseCloudName.C
    ${CLOUDS}/Templates/SprayCloud/SprayCloudName.C

    # clouds
    ${DERIVEDCLOUDS}/momentumCloud/momentumCloud.C
    ${DERIVEDCLOUDS}/collidingCloud/collidingCloud.C
    ${DERIVEDCLOUDS}/mppicCloud/mppicCloud.C
    ${DERIVEDCLOUDS}/thermoCloud/thermoCloud.C
    ${DERIVEDCLOUDS}/reactingCloud/reactingCloud.C
    ${DERIVEDCLOUDS}/reactingMultiphaseCloud/reactingMultiphaseCloud.C
    ${DERIVEDCLOUDS}/sprayCloud/sprayCloud.C

    # parcel names
    ${PARCELS}/Templates/MomentumParcel/MomentumParcelName.C
    ${PARCELS}/Templates/CollidingParcel/CollidingParcelName.C
    ${PARCELS}/Templates/MPPICParcel/MPPICParcelName.C
    ${PARCELS}/Templates/ReactingMultiphaseParcel/ReactingMultiphaseParcelName.C
    ${PARCELS}/Templates/ReactingParcel/ReactingParcelName.C
    ${PARCELS}/Templates/SprayParcel/SprayParcelName.C
    ${PARCELS}/Templates/ThermoParcel/ThermoParcelName.C

    # sub-models
    submodels/subModelBase/subModelBase.C
    ${DERIVEDPARCELS}/momentumParcel/makeMomentumParcelSubmodels.C
    ${DERIVEDPARCELS}/collidingParcel/makeCollidingParcelSubmodels.C
    ${DERIVEDPARCELS}/mppicParcel/makeMppicParcelSubmodels.C
    ${DERIVEDPARCELS}/thermoParcel/makeThermoParcelSubmodels.C
    ${DERIVEDPARCELS}/reactingParcel/makeReactingParcelSubmodels.C
    ${DERIVEDPARCELS}/reactingMultiphaseParcel/makeReactingMultiphaseParcelSubmodels.C
    ${DERIVEDPARCELS}/sprayParcel/makeSprayParcelSubmodels.C
)

# bolt-on models
set(RADIATION submodels/addOns/radiation)
target_sources(${target_name} PRIVATE
    ${RADIATION}/absorptionEmission/cloudAbsorptionEmission/cloudAbsorptionEmission.C
    ${RADIATION}/scatter/cloudScatter/cloudScatter.C
)

set(MOMENTUMINJECTION submodels/Momentum/InjectionModel)
target_sources(${target_name} PRIVATE
    ${MOMENTUMINJECTION}/MomentumLookupTableInjection/momentumParcelInjectionData.C
    ${MOMENTUMINJECTION}/MomentumLookupTableInjection/momentumParcelInjectionDataIO.C
    ${MOMENTUMINJECTION}/MomentumLookupTableInjection/momentumParcelInjectionDataIOList.C
    ${MOMENTUMINJECTION}/PatchInjection/patchInjectionBase.C
)

set(THERMOINJECTION submodels/Thermodynamic/InjectionModel)
target_sources(${target_name} PRIVATE
    ${THERMOINJECTION}/ThermoLookupTableInjection/thermoParcelInjectionData.C
    ${THERMOINJECTION}/ThermoLookupTableInjection/thermoParcelInjectionDataIO.C
    ${THERMOINJECTION}/ThermoLookupTableInjection/thermoParcelInjectionDataIOList.C
)

set(REACTINGINJECTION submodels/Reacting/InjectionModel)
target_sources(${target_name} PRIVATE
    ${REACTINGINJECTION}/ReactingLookupTableInjection/reactingParcelInjectionData.C
    ${REACTINGINJECTION}/ReactingLookupTableInjection/reactingParcelInjectionDataIO.C
    ${REACTINGINJECTION}/ReactingLookupTableInjection/reactingParcelInjectionDataIOList.C
)

set(REACTINGMPINJECTION submodels/ReactingMultiphase/InjectionModel)
target_sources(${target_name} PRIVATE
    ${REACTINGMPINJECTION}/ReactingMultiphaseLookupTableInjection/reactingMultiphaseParcelInjectionData.C
    ${REACTINGMPINJECTION}/ReactingMultiphaseLookupTableInjection/reactingMultiphaseParcelInjectionDataIO.C
    ${REACTINGMPINJECTION}/ReactingMultiphaseLookupTableInjection/reactingMultiphaseParcelInjectionDataIOList.C
)

set(MPPICPARTICLESTRESS submodels/MPPIC/ParticleStressModels)
target_sources(${target_name} PRIVATE
    ${MPPICPARTICLESTRESS}/ParticleStressModel/ParticleStressModel.C
    ${MPPICPARTICLESTRESS}/HarrisCrighton/HarrisCrighton.C
    ${MPPICPARTICLESTRESS}/Lun/Lun.C
    ${MPPICPARTICLESTRESS}/exponential/exponential.C
)

set(MPPICCORRECTIONLIMITING submodels/MPPIC/CorrectionLimitingMethods)
target_sources(${target_name} PRIVATE
    ${MPPICCORRECTIONLIMITING}/CorrectionLimitingMethod/CorrectionLimitingMethod.C
    ${MPPICCORRECTIONLIMITING}/noCorrectionLimiting/noCorrectionLimiting.C
    ${MPPICCORRECTIONLIMITING}/absolute/absolute.C
    ${MPPICCORRECTIONLIMITING}/relative/relative.C
)

set(MPPICTIMESCALE submodels/MPPIC/TimeScaleModels)
target_sources(${target_name} PRIVATE
    ${MPPICTIMESCALE}/TimeScaleModel/TimeScaleModel.C
    ${MPPICTIMESCALE}/equilibrium/equilibrium.C
    ${MPPICTIMESCALE}/nonEquilibrium/nonEquilibrium.C
    ${MPPICTIMESCALE}/isotropic/isotropic.C
)

target_sources(${target_name} PRIVATE
    # injection model
    submodels/Momentum/InjectionModel/InjectionModel/injectionModel.C

    # integration schemes
    integrationScheme/integrationScheme/integrationScheme.C
    integrationScheme/integrationScheme/integrationSchemeNew.C
    integrationScheme/Euler/Euler.C
    integrationScheme/analytical/analytical.C

    # phase properties
    phaseProperties/phaseProperties/phaseProperties.C
    phaseProperties/phaseProperties/phasePropertiesIO.C
    phaseProperties/phasePropertiesList/phasePropertiesList.C

    # additional helper classes
    clouds/Templates/MomentumCloud/cloudSolution/cloudSolution.C

    # averaging methods
    submodels/MPPIC/AveragingMethods/makeAveragingMethods.C

    # fvModels
    fvModels/clouds/clouds.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_include_directories(${target_name} PRIVATE
    ${LIB_SRC}/tracking/lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    lagrangian 
    physicalProperties 
    specie 
    fluidThermophysicalModels 
    thermophysicalProperties 
    multicomponentThermophysicalModels 
    momentumTransportModels 
    incompressibleMomentumTransportModels 
    compressibleMomentumTransportModels 
    radiationModels 
    sampling 
    finiteVolume 
    meshTools
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



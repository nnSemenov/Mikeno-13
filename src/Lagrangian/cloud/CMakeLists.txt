lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name LagrangianCloud)

add_library(${target_name} SHARED
    # Base Cloud
    cloud/cloud.C

    # Cloud Mix-ins
    clouds/shaped/shaped.C
    clouds/spherical/spherical.C
    clouds/coupled/coupled.C
    clouds/coupledToIncompressibleFluid/coupledToIncompressibleFluid.C
    clouds/coupledToFluid/coupledToFluid.C
    clouds/sphericalCoupled/sphericalCoupled.C
    clouds/massive/massive.C
    clouds/grouped/grouped.C

    # Derived Clouds
    clouds/kinematicParticle/kinematicParticle.C
    clouds/kinematicParcel/kinematicParcel.C
    clouds/particle/particle.C
    clouds/parcel/parcel.C

    # Patches
    derivedLagrangianPatches/cloudVelocity/cloudVelocityLagrangianPatch.C

    # Patch Fields
    fields/derivedLagrangianPatchFields/cloudVelocity/cloudVelocityLagrangianPatchVectorField.C
    fields/derivedLagrangianPatchFields/reboundVelocity/reboundVelocityLagrangianPatchVectorField.C
    fields/derivedLagrangianPatchFields/stickVelocity/stickVelocityLagrangianPatchVectorField.C
    fields/derivedLagrangianPatchFields/escapeVelocity/escapeVelocityLagrangianPatchVectorField.C

    # Field Sources
    fields/derivedLagrangianFieldSources/mass/massLagrangianScalarFieldSource.C
    fields/derivedLagrangianFieldSources/volume/volumeLagrangianScalarFieldSource.C
    fields/derivedLagrangianFieldSources/surfaceArea/surfaceAreaLagrangianScalarFieldSource.C
    fields/derivedLagrangianFieldSources/coneVelocity/coneVelocityLagrangianVectorFieldSource.C
    fields/derivedLagrangianFieldSources/coneDiskVelocity/coneDiskVelocityLagrangianVectorFieldSource.C
    fields/derivedLagrangianFieldSources/uniformSizeNumber/uniformSizeNumberLagrangianScalarFieldSource.C
    fields/derivedLagrangianFieldSources/flowRateNumber/flowRateNumberLagrangianScalarFieldSource.C
    fields/derivedLagrangianFieldSources/totalNumber/totalNumberLagrangianScalarFieldSource.C
    fields/derivedLagrangianFieldSources/distributionDiameter/distributionDiameterLagrangianScalarFieldSource.C
    fields/derivedLagrangianFieldSources/totalPressureVelocity/totalPressureVelocityLagrangianVectorFieldSource.C
    fields/derivedLagrangianFieldSources/carrier/carrierLagrangianFieldSources.C

    # Models
    LagrangianModels/cloudLagrangianModel/cloudLagrangianModel.C
    LagrangianModels/constantCoefficientVirtualMass/constantCoefficientVirtualMass.C
    LagrangianModels/drag/drag.C
    LagrangianModels/GidaspowErgunWenYuDrag/GidaspowErgunWenYuDrag.C
    LagrangianModels/gravity/gravity.C
    LagrangianModels/pressureGradientForce/pressureGradientForce.C
    LagrangianModels/SaffmanMeiLift/SaffmanMeiLift.C
    LagrangianModels/SchillerNaumannDrag/SchillerNaumannDrag.C
    LagrangianModels/turbulentDispersion/turbulentDispersion.C
    LagrangianModels/pointInjection/pointInjection.C
    LagrangianModels/patchInjection/patchInjection.C
    LagrangianModels/volumeInjection/volumeInjection.C
    LagrangianModels/manualInjection/manualInjection.C
    LagrangianModels/diskInjection/diskInjection.C

    # Base Cloud-Post-Processing Function Objects
    cloudFunctionObject/cloudFunctionObject.C
    cloudFunctionObject/cloudLagrangianMeshFunctionObject.C
    cloudFunctionObject/cloudFvMeshFunctionObject.C
    cloudFunctionObject/cloudFunctionObjectUList.C

    # Cloud-Solving FvModel
    fvModel/cloud_fvModel.C

    # Cloud-Solving Function Object
    functionObject/cloud_functionObject.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_include_directories(${target_name} PRIVATE

)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    physicalProperties 
    fluidThermophysicalModels 
    momentumTransportModels 
    finiteVolume 
    meshTools 
    Lagrangian
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name interfaceProperties)

add_library(${target_name} SHARED
    interfaceProperties.C

    surfaceTensionModels/surfaceTensionModel/surfaceTensionModel.C
    surfaceTensionModels/surfaceTensionModel/surfaceTensionModelNew.C
    surfaceTensionModels/constant/constantSurfaceTension.C
    surfaceTensionModels/temperatureDependent/temperatureDependentSurfaceTension.C

    contactAngleModels/contactAngleModel/contactAngleModel.C
    contactAngleModels/contactAngleModel/contactAngleModelNew.C
    contactAngleModels/constant/constantContactAngle.C
    contactAngleModels/temperatureDependent/temperatureDependentContactAngle.C
    contactAngleModels/dynamic/dynamicContactAngle.C
    contactAngleModels/gravitational/gravitationalContactAngle.C

    contactAngle/contactAngleFvPatchScalarField.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
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



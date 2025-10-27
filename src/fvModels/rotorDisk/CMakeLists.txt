lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name rotorDisk)

add_library(${target_name} SHARED
    rotorDisk.C
    bladeModel/bladeModel.C
    profileModel/profileModel.C
    profileModel/profileModelList.C
    profileModel/lookup/lookupProfile.C
    profileModel/series/seriesProfile.C
    trimModel/trimModel/trimModel.C
    trimModel/trimModel/trimModelNew.C
    trimModel/fixed/fixedTrim.C
    trimModel/targetCoeff/targetCoeffTrim.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_include_directories(${target_name} PRIVATE
    ${LIB_SRC}/physicalProperties/lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    finiteVolume 
    sampling 
    meshTools 
    momentumTransportModels 
    compressibleMomentumTransportModels 
    fluidThermoThermophysicalTransportModels
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



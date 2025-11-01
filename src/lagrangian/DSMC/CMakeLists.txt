lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name DSMC)

add_library(${target_name} SHARED
    # Parcels
    parcels/derived/dsmcParcel/dsmcParcel.C

    # Cloud name
    clouds/Templates/DSMCCloud/DSMCCloudName.C

    # Sub-models
    parcels/derived/dsmcParcel/makeDSMCParcelBinaryCollisionModels.C
    parcels/derived/dsmcParcel/makeDSMCParcelWallInteractionModels.C
    parcels/derived/dsmcParcel/makeDSMCParcelInflowBoundaryModels.C
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
    finiteVolume
    meshTools
    Pstream_best
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



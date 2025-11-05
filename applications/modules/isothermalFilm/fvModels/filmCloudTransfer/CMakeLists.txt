lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name filmCloudTransfer)

add_library(${target_name} SHARED
    filmCloudTransfer.C
    ejectionModels/ejectionModel/ejectionModel.C
    ejectionModels/ejectionModel/ejectionModelNew.C
    ejectionModels/dripping/dripping.C
    ejectionModels/BrunDripping/BrunDripping.C
    ejectionModels/curvatureSeparation/curvatureSeparation.C

    cloudFilmTransfer/CloudFilmTransfer/CloudFilmTransferBase.C
    cloudFilmTransfer/makeThermoParcelCloudFilmTransfer.C
    cloudFilmTransfer/makeReactingParcelCloudFilmTransfer.C
    cloudFilmTransfer/makeReactingMultiphaseParcelCloudFilmTransfer.C
    cloudFilmTransfer/makeSprayParcelCloudFilmTransfer.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_include_directories(${target_name} PRIVATE
    ${LIB_SRC}/physicalProperties/lnInclude
    ${LIB_SRC}/thermophysicalModels/basic/lnInclude
    ${LIB_SRC}/thermophysicalModels/specie/lnInclude
    ${LIB_SRC}/MomentumTransportModels/momentumTransportModels/lnInclude
    ${LIB_SRC}/MomentumTransportModels/compressible/lnInclude
    ${LIB_SRC}/twoPhaseModels/interfaceProperties/lnInclude

    ${LIB_SRC}/tracking/lnInclude
#    ${LIB_SRC}/lagrangian/basic/lnInclude
#    ${LIB_SRC}/lagrangian/parcel/lnInclude
    ${LIB_SRC}/thermophysicalModels/thermophysicalProperties/lnInclude
    ${LIB_SRC}/thermophysicalModels/multicomponentThermo/lnInclude

    ${LIB_SRC}/finiteVolume/lnInclude
    ${LIB_SRC}/meshTools/lnInclude
    
    ${FOAM_MODULES}/isothermalFilm/filmCompressibleMomentumTransportModels/lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    isothermalFilm
    lagrangian
    lagrangianParcel
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name extrudeModel)

add_library(${target_name} SHARED
    extrudeModel/extrudeModel.C
    extrudeModel/extrudeModelNew.C
    linearNormal/linearNormal.C
    planeExtrusion/planeExtrusion.C
    linearDirection/linearDirection.C
    linearRadial/linearRadial.C
    path/path.C
    sphericalRadial/sphericalRadial.C
    cylindricalRadial/cylindricalRadial.C
    sigmaRadial/sigmaRadial.C
    sector/sector.C
    cyclicSector/cyclicSector.C
    wedge/wedge.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
    ${LIB_SRC}/polyTopoChange/lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    meshTools
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



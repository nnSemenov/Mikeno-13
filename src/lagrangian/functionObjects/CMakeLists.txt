lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name lagrangianFunctionObjects)

add_library(${target_name} SHARED
    cloudInfo/cloudInfo.C
    dsmcFields/dsmcFields.C
    particles/particles.C
    stopAtEmptyClouds/stopAtEmptyClouds.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_include_directories(${target_name} PRIVATE
    ${LIB_SRC}/tracking/lnInclude
    ${LIB_SRC}/lagrangian/DSMC/lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    finiteVolume 
    physicalProperties 
    meshTools 
    lagrangian 
    lagrangianParcel 
    utilityFunctionObjects
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



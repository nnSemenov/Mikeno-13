lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name solverFunctionObjects)

add_library(${target_name} SHARED
    age/age.C
    scalarTransport/scalarTransport.C
    phaseScalarTransport/phaseScalarTransport.C
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
    specie 
    interfaceCompression 
    momentumTransportModels 
    incompressibleMomentumTransportModels 
    compressibleMomentumTransportModels 
    finiteVolume 
    meshTools 
    fvModels 
    fvConstraints
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name compressibleInterfaceProperties)

add_library(${target_name} SHARED
    surfaceTensionModels/liquidProperties/liquidPropertiesSurfaceTension.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    physicalProperties 
    fluidThermophysicalModels 
    specie 
    thermophysicalProperties 
    twoPhaseProperties 
    interfaceProperties 
    finiteVolume
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



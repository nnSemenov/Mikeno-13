lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name rhoPorousSimpleFoam)

add_executable(${target_name}
    rhoPorousSimpleFoam.C
)

target_include_directories(${target_name} PRIVATE
    lnInclude
    ${LIB_SRC}/finiteVolume/cfdTools
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OSspecific
    OpenFOAM

    fluidThermophysicalModels
    specie
    physicalProperties
    compressibleMomentumTransportModels
    momentumTransportModels
    coupledThermophysicalTransportModels
    finiteVolume
    sampling
    meshTools
    fvModels
    fvConstraints
    Pstream_best
    thermophysicalTransportModel
    fluidThermophysicalTransportModel
    fluidThermoThermophysicalTransportModels
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=libNULL.so
)

set(FOAM_regular_executables "${FOAM_regular_executables};${target_name}" PARENT_SCOPE)
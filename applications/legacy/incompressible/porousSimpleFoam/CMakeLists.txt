lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name porousSimpleFoam)

add_executable(${target_name}
    porousSimpleFoam.C
)

target_include_directories(${target_name} PRIVATE
    lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OSspecific
    OpenFOAM

    momentumTransportModels
    incompressibleMomentumTransportModels
    physicalProperties
    finiteVolume
    meshTools
    fvModels
    fvConstraints
    sampling
    Pstream_best
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=libNULL.so
)

set(FOAM_regular_executables "${FOAM_regular_executables};${target_name}" PARENT_SCOPE)
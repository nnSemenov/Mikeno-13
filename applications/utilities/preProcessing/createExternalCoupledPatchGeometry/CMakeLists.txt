lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name createExternalCoupledPatchGeometry)

add_executable(${target_name}
    createExternalCoupledPatchGeometry.C
)

target_include_directories(${target_name} PRIVATE
    lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OSspecific
    OpenFOAM

    physicalProperties 
    momentumTransportModels 
    compressibleMomentumTransportModels 
    Pstream_best
    finiteVolume 
    fvModels 
    meshTools
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=libNULL.so
)

set(FOAM_regular_executables "${FOAM_regular_executables};${target_name}" PARENT_SCOPE)
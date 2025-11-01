lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name chemFoam)

add_executable(${target_name}
    chemFoam.C
)

target_include_directories(${target_name} PRIVATE
    lnInclude
    ${LIB_SRC}/physicalProperties/lnInclude
    ${LIB_SRC}/thermophysicalModels/specie/lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OSspecific
    OpenFOAM

    chemistryModel 
    finiteVolume 
    meshTools 
    Pstream_best
    fluidThermophysicalModels 
    chemistryModel
    multicomponentThermophysicalModels
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=libNULL.so
)

set(FOAM_regular_executables "${FOAM_regular_executables};${target_name}" PARENT_SCOPE)
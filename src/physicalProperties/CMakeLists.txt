lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

add_library(physicalProperties SHARED
    physicalProperties/physicalProperties.C
    viscosity/viscosity.C
    viscosityModels/viscosityModel/viscosityModel.C
    viscosityModels/viscosityModel/viscosityModelNew.C
    viscosityModels/constant/constantViscosityModel.C
)
target_include_directories(physicalProperties PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_link_libraries(physicalProperties PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific
    finiteVolume
    Pstream_dummy
)

install(TARGETS physicalProperties
    DESTINATION lib
)
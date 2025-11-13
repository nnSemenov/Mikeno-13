lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

add_library(laminarFlameSpeedModels SHARED
    laminarFlameSpeed/laminarFlameSpeed.C
    laminarFlameSpeed/laminarFlameSpeedNew.C
    constant/constant.C
    Gulder/Gulder.C
    RaviPetersen/RaviPetersen.C
)
target_include_directories(laminarFlameSpeedModels PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_include_directories(laminarFlameSpeedModels PRIVATE
    ${LIB_SRC}/physicalProperties/lnInclude
    ${LIB_SRC}/thermophysicalModels/specie/lnInclude 
    ${LIB_SRC}/thermophysicalModels/basic/lnInclude 
    ${LIB_SRC}/thermophysicalModels/multicomponentThermo/lnInclude
)
target_link_libraries(laminarFlameSpeedModels PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    finiteVolume
)

target_compile_definitions(laminarFlameSpeedModels PRIVATE
    LIB_NAME=liblaminarFlameSpeedModels.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};laminarFlameSpeedModels" PARENT_SCOPE)



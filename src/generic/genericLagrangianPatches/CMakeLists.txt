lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

add_library(genericLagrangianPatches SHARED
    genericLagrangianPatch/genericLagrangianPatch.C
)

target_include_directories(genericLagrangianPatches PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_link_libraries(genericLagrangianPatches PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    genericPatches
    Lagrangian
)

install(TARGETS genericLagrangianPatches
    DESTINATION lib
)
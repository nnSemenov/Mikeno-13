lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

add_library(genericLagrangianFields SHARED
    genericLagrangianPatchField/genericLagrangianPatchFields.C
    genericLagrangianFieldSource/genericLagrangianFieldSources.C
)

target_include_directories(genericLagrangianFields PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_link_libraries(genericLagrangianFields PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    genericPatches
    genericFields
    genericLagrangianPatches
    Lagrangian
)

install(TARGETS genericLagrangianFields
    DESTINATION lib
)
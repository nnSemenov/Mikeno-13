lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

add_library(genericFvFields SHARED
    genericFvPatchField/genericFvPatchFields.C
    genericFvFieldSource/genericFvFieldSources.C
)

target_include_directories(genericFvFields PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_link_libraries(genericFvFields PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    genericPatches
    genericFields
    genericFvPatches
    finiteVolume
)

install(TARGETS genericFvFields
    DESTINATION lib
)
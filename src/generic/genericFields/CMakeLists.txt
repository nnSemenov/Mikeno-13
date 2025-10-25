lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

add_library(genericFields SHARED
    genericFieldBase/genericFieldBase.C
    genericPointPatchField/genericPointPatchFields.C
)

target_include_directories(genericFields PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_link_libraries(genericFields PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    genericPatches
)

install(TARGETS genericFields
    DESTINATION lib
)
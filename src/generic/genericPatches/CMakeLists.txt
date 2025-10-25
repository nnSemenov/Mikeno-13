lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

add_library(genericPatches SHARED
    genericPolyPatch/genericPolyPatch.C
    genericPointPatch/genericPointPatch.C
)

target_include_directories(genericPatches PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_link_libraries(genericPatches PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific
)

install(TARGETS genericPatches
    DESTINATION lib
)
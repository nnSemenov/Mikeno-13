lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

add_library(genericFvPatches SHARED
    genericFvPatch/genericFvPatch.C
)

target_include_directories(genericFvPatches PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_link_libraries(genericFvPatches PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    genericPatches
    finiteVolume
)

install(TARGETS genericFvPatches
    DESTINATION lib
)
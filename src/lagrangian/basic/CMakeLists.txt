lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

add_library(lagrangian SHARED
    particle/particle.C
    particle/particleIO.C

    IOPosition/IOPositionName.C

    cloud/cloud.C

    passiveParticle/passiveParticleCloud.C

    InteractionLists/referredWallFace/referredWallFace.C
)

target_include_directories(lagrangian PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_link_libraries(lagrangian PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    meshTools
    tracking
)

install(TARGETS lagrangian
    DESTINATION lib
)
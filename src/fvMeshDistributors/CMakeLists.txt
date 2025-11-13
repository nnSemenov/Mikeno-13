lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name fvMeshDistributors)

add_library(${target_name} SHARED
    distributor/distributor_fvMeshDistributor.C
    loadBalancer/loadBalancer_fvMeshDistributor.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    decompositionMethods 
    Pstream_best
    #scotchDecomp
    #ptscotchDecomp 
    triSurface 
    meshTools 
    polyTopoChange 
    finiteVolume 
    fvMeshStitchers
)

if(TARGET scotchDecomp)
    target_link_libraries(${target_name} PRIVATE
        scotchDecomp
    )
endif()

if(TARGET ptscotchDecomp)
    target_link_libraries(${target_name} PRIVATE
        ptscotchDecomp
    )
endif()

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



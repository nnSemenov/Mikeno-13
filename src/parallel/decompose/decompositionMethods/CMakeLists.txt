lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name decompositionMethods)

add_library(${target_name} SHARED
    decompositionMethod/decompositionMethod.C
    geometric/geometric.C
    simple/simple.C
    hierarchical/hierarchical.C
    manual/manual.C
    multiLevel/multiLevel.C
    structured/structured.C
    random/random.C
    none/none.C
)

set(decompositionConstraints decompositionConstraints)
target_sources(${target_name} PRIVATE
    ${decompositionConstraints}/decompositionConstraint/decompositionConstraint.C
    ${decompositionConstraints}/preserveBaffles/preserveBafflesConstraint.C
    ${decompositionConstraints}/preserveFaceZones/preserveFaceZonesConstraint.C
    ${decompositionConstraints}/preservePatches/preservePatchesConstraint.C
    ${decompositionConstraints}/singleProcessorFaceSets/singleProcessorFaceSetsConstraint.C
    ${decompositionConstraints}/refinementHistory/refinementHistoryConstraint.C

)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    meshTools
    polyTopoChange
    finiteVolume
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



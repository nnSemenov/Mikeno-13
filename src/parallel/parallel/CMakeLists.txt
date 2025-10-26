lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name parallel)

add_library(${target_name} SHARED
    processorRunTimes/processorRunTimes.C

    domainDecomposition/domainDecomposition.C
    domainDecomposition/domainDecompositionDecompose.C
    domainDecomposition/domainDecompositionReconstruct.C
    domainDecomposition/domainDecompositionNonConformal.C

    multiDomainDecomposition/multiDomainDecomposition.C

    fieldDecomposers/fvFieldDecomposer/fvFieldDecomposer.C
    fieldDecomposers/pointFieldDecomposer/pointFieldDecomposer.C
    fieldDecomposers/lagrangianFieldDecomposer/lagrangianFieldDecomposer.C
    fieldDecomposers/LagrangianFieldDecomposer/LagrangianFieldDecomposer.C

    fieldReconstructors/fvFieldReconstructor/fvFieldReconstructor.C
    fieldReconstructors/pointFieldReconstructor/pointFieldReconstructor.C
    fieldReconstructors/lagrangianFieldReconstructor/lagrangianFieldReconstructor.C
    fieldReconstructors/LagrangianFieldReconstructor/LagrangianFieldReconstructor.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_include_directories(${target_name} PRIVATE
    ${LIB_SRC}/tracking/lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    finiteVolume
    #metisDecomp
    #scotchDecomp
    meshTools
    decompositionMethods
    Pstream_dummy
    polyTopoChange
    lagrangian
    Lagrangian
)

set(possible_targets metisDecomp scotchDecomp)
foreach(target ${possible_targets})
    if(TARGET ${target})
	target_link_libraries(${target_name} PRIVATE ${target})
    endif()
endforeach()

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



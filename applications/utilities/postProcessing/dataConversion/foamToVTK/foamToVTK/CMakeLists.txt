lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name foamToVTK)

add_library(${target_name} SHARED
    surfaceMeshWriter.C
    internalWriter.C
    lagrangianWriter.C
    patchWriter.C
    writeFaceSet.C
    writePointSet.C
    writeSurfFields.C
    vtkMesh.C
    vtkTopo.C

    writeVTK/writeVTK.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_include_directories(${target_name} PRIVATE
    ${LIB_SRC}/tracking/lnInclude
    ${LIB_SRC}/meshTools/lnInclude
    ${LIB_SRC}/finiteVolume/lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    polyTopoChange 
    lagrangian 
    genericFvFields 
    fileFormats
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)



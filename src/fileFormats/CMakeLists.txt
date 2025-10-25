lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

add_library(fileFormats SHARED
    vtk/vtkWriteOps.C
    vtk/vtkUnstructuredReader.C
    nas/NASCore.C
    starcd/STARCDCore.C
    obj/OBJstream.C
)
target_include_directories(fileFormats PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_compile_definitions(fileFormats PRIVATE
    LIB_NAME=libfileFormats.so
)

target_link_libraries(fileFormats PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific
)


set(FOAM_regular_libraries "${FOAM_regular_libraries};fileFormats" PARENT_SCOPE)



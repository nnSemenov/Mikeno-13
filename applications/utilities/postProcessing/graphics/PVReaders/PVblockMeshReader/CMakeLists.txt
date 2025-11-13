project(PVblockMeshReader)

find_package(ParaView REQUIRED)

if(${ParaView_VERSION} VERSION_LESS 5.7)
    # ParaView-5.7.x and lower will prepend "lib" to the target name
    set(TARGET_NAME PVblockMeshReader_SM)
else()
    set(TARGET_NAME libPVblockMeshReader_SM)
endif()

if(${ParaView_VERSION} VERSION_LESS 5.7)
    # ParaView-5.7.x and lower requires the paraview include file
    include(${PARAVIEW_USE_FILE})
endif()

#target_link_directories(
#    ${TARGET_NAME} PUBLIC
#    $ENV{FOAM_LIBBIN}
#    $ENV{FOAM_EXT_LIBBIN}
#    $ENV{PV_PLUGIN_PATH}
#)
#
#target_include_directories(
#    ${TARGET_NAME} PUBLIC
#    ${PROJECT_SOURCE_DIR}/
#    ${PROJECT_SOURCE_DIR}/vtk
#)

# Add the plugin
if(${ParaView_VERSION} VERSION_LESS 5.7)
    ADD_PARAVIEW_PLUGIN(
        ${TARGET_NAME}
        "1.0"
        SERVER_MANAGER_XML PVblockMeshReader_SM.xml
        SERVER_MANAGER_SOURCES vtk/vtkPVblockMeshReader.cxx
    )
else()
    # Paraview-5.7.x and higher builds the vtk module separately
    PARAVIEW_ADD_PLUGIN(
        ${TARGET_NAME}
        VERSION "1.0"
        SERVER_MANAGER_XML PVblockMeshReader_SM.xml
        MODULES PVblockMeshReader_VTK
        MODULE_FILES "vtk/vtk.module"
    )
endif()

# Set the output library destination to the plugin directory
#set_target_properties(
#    ${TARGET_NAME}
#    PROPERTIES
#    LIBRARY_OUTPUT_DIRECTORY "$ENV{PV_PLUGIN_PATH}"
#)

target_link_libraries(${TARGET_NAME} PUBLIC
    vtkPVblockMesh
    OpenFOAM_Defines
    OpenFOAM
    OSspecific
)

target_include_directories(${TARGET_NAME} PUBLIC
    ../vtkPVblockMesh
)

# Build the plugin
if(${ParaView_VERSION} VERSION_LESS 5.5)
    target_link_libraries(${TARGET_NAME} PRIVATE
        pqCore
    )
elseif(${ParaView_VERSION} VERSION_LESS 5.7)
    # Assume QT version 5 if it hasn't been defined
    if(NOT PARAVIEW_QT_MAJOR_VERSION)
        set(PARAVIEW_QT_MAJOR_VERSION 5)
    endif()
    # Paraview-5.5.x and higher needs QT libraries listed in the link command
    # in order for the headers to be available
    target_link_libraries(${TARGET_NAME} PUBLIC
        Qt${PARAVIEW_QT_MAJOR_VERSION}::Core
        Qt${PARAVIEW_QT_MAJOR_VERSION}::Gui
        PRIVATE
        pqCore
    )
else()
    # Assume QT version 5 if it hasn't been defined
    if(NOT PARAVIEW_QT_MAJOR_VERSION)
        set(PARAVIEW_QT_MAJOR_VERSION 5)
    endif()
    # Paraview-5.5.x and higher needs QT libraries listed in the link command
    # in order for the headers to be available
    target_link_libraries(${TARGET_NAME}
        PUBLIC
        Qt${PARAVIEW_QT_MAJOR_VERSION}::Core
        Qt${PARAVIEW_QT_MAJOR_VERSION}::Gui
        PRIVATE
        ParaView::pqCore
    )
endif()

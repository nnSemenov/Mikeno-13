
find_package(ParaView REQUIRED)

PARAVIEW_PLUGIN_SCAN(
    PLUGIN_FILES
        "PVblockMeshReader/paraview.plugin"
        "PVFoamReader/paraview.plugin"
    PROVIDES_PLUGINS plugins
    ENABLE_BY_DEFAULT ON
)

PARAVIEW_PLUGIN_BUILD(PLUGINS ${plugins})

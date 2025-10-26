file(GLOB config_files "${CMAKE_SOURCE_DIR}/cmake/3rdParty/*.cmake")

foreach (config_file ${config_files})
    include(${config_file})
endforeach ()
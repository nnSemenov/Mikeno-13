


lnInclude(OpenFOAM RESULT_DIR OpenFOAM_lnInclude_dir)
message(STATUS "OpenFOAM_lnInclude_dir = ${OpenFOAM_lnInclude_dir}")

add_subdirectory(OSspecific/POSIX)
add_subdirectory(Pstream)
add_subdirectory(OpenFOAM)
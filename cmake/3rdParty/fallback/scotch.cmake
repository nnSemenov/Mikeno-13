
find_file(scotch_header
	NAMES scotch.h
	PATH_SUFFIXES scotch
	REQUIRED
)
message(STATUS "Found scotch header file: ${scotch_header}")
cmake_path(GET scotch_header PARENT_PATH scotch_include_dir)

####################
find_library(scotch_lib 
	NAMES scotch
	REQUIRED
)
message(STATUS "Found scotch lib: ${scotch_lib}")

add_library(scotch_imported INTERFACE)
target_link_libraries(scotch_imported INTERFACE ${scotch_lib})
target_include_directories(scotch_imported INTERFACE ${scotch_include_dir})

add_library(SCOTCH::scotch ALIAS scotch_imported)

######################
find_library(scotch_err_lib
	NAMES scotcherr
	REQUIRED
)
message(STATUS "Found scotcherr lib: ${scotch_err_lib}")

add_library(scotcherr_imported INTERFACE)
target_link_libraries(scotcherr_imported INTERFACE ${scotch_err_lib})
target_include_directories(scotcherr_imported INTERFACE ${scotch_include_dir})

add_library(SCOTCH::scotcherr ALIAS scotcherr_imported)

set(SCOTCH_OK ON)
######################
######################

find_file(ptscotch_header
	NAMES ptscotch.h
	PATH_SUFFIXES scotch
)
if(NOT ${ptscotch_header})
	message(WARNING "Failed to find ptscotch header. Skip ptscotch")
	return()
endif ()
message(STATUS "Found ptscotch header file: ${ptscotch_header}")
cmake_path(GET ptscotch_header PARENT_PATH ptscotch_include_dir)

#####################
find_library(ptscotch_lib
	NAMES ptscotch
	REQUIRED
)
message(STATUS "Found ptscotch lib: ${ptscotch_lib}")

add_library(ptscotch_imported INTERFACE)
target_link_libraries(ptscotch_imported INTERFACE ${ptscotch_lib})
target_include_directories(ptscotch_imported INTERFACE ${ptscotch_include_dir})

add_library(SCOTCH::ptscotch ALIAS ptscotch_imported)

set(PTSCOTCH_OK ON)

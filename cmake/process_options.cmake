add_library(OpenFOAM_Defines INTERFACE)

target_compile_features(OpenFOAM_Defines INTERFACE
    cxx_std_17)

set(valid_label_size 32 64)
if(NOT ${WM_LABEL_SIZE} IN_LIST valid_label_size)
    message(FATAL_ERROR "WM_LABEL_SIZE = ${WM_LABEL_SIZE}")
endif ()
target_compile_definitions(OpenFOAM_Defines INTERFACE
    WM_LABEL_SIZE=${WM_LABEL_SIZE}
)

set(valid_precision_option SP DP LP)
if(NOT ${WM_PRECISION_OPTION} IN_LIST valid_precision_option)
    message(FATAL_ERROR "WM_PRECISION_OPTION = ${WM_PRECISION_OPTION}")
endif ()
target_compile_definitions(OpenFOAM_Defines INTERFACE
    WM_${WM_PRECISION_OPTION}
)

target_compile_definitions(OpenFOAM_Defines INTERFACE
    ${WM_ARCH}
    WM_ARCH_OPTION=${WM_ARCH_OPTION}
    NoRepository
)

target_compile_options(OpenFOAM_Defines INTERFACE
    -Wall
    -Wextra
    -Wold-style-cast
    -Wnon-virtual-dtor
    -Wno-unused-parameter
    -Wno-invalid-offsetof
    -Wno-undefined-var-template
    -Wno-unqualified-std-cast-call
    -ftemplate-depth-256

    # less warn
#    -Wno-old-style-cast
#    -Wno-unused-local-typedefs
#    -Wno-tautological-undefined-compare
#    -Wno-shift-negative-value
)

# Install this interface target
install(TARGETS OpenFOAM_Defines
    EXPORT MikenoTargets
)
set(FOAM_special_libraries "${FOAM_special_libraries};OpenFOAM_Defines")

####### wmake env vars
set(WM_PROJECT_DIR ${PROJECT_SOURCE_DIR})
set(WM_CC ${CMAKE_C_COMPILER})
set(WM_CXX ${CMAKE_CXX_COMPILER})
set(WM_PROJECT ${PROJECT_NAME})
set(WM_COMPILER_LIB_ARCH ${WM_ARCH_OPTION})
set(WM_LINK_LANGUAGE ${CMAKE_CXX_LINK_EXECUTABLE})
set(WM_COMPILER_TYPE system)
set(WM_PROJECT_VERSION ${PROJECT_VERSION})
set(WM_DIR ${WM_PROJECT_DIR}/wmake)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    set(WM_COMPILER Gcc)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set(WM_COMPILER Clang)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Intel")
    set(WM_COMPILER Icx)
else ()
    set(WM_COMPILER Unknown)
    message(WARNING "Unknown C++ compiler id ${CMAKE_CXX_COMPILER_ID}, WM_COMPILER is set to ${CMAKE_CXX_COMPILER_ID}")
endif ()

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    set(WM_COMPILE_OPTION Debug)
elseif (${CMAKE_BUILD_TYPE} STREQUAL Release)
    set(WM_COMPILE_OPTION Opt)
elseif (${CMAKE_BUILD_TYPE} STREQUAL MinSizeRel)
    set(WM_COMPILE_OPTION Opt)
elseif (${CMAKE_BUILD_TYPE} STREQUAL RelWithDebInfo)
    set(WM_COMPILE_OPTION Prof)
else ()
    set(WM_COMPILE_OPTION Unknown)
    message(WARNING "Unknown CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE}, WM_COMPILE_OPTION is set to Unknown")
endif ()



set(WM_OPTIONS "${WM_ARCH}${WM_COMPILER}${WM_PRECISION_OPTION}Int${WM_LABEL_SIZE}${WM_COMPILE_OPTION}")
message(STATUS "WM_OPTIONS = ${WM_OPTIONS}")
set(CMAKE_INSTALL_PREFIX ${WM_PROJECT_DIR}/platforms/${WM_OPTIONS})

get_target_property(TEMP_CXXFlags OpenFOAM_Defines INTERFACE_COMPILE_OPTIONS)
get_target_property(TEMP_CXXFeatures OpenFOAM_Defines INTERFACE_COMPILE_FEATURES)
# set(WM_CXXFLAGS "${TEMP_CXXFlags} -std=c++17")
string(REPLACE ";" "\ " WM_CXXFLAGS "${TEMP_CXXFlags} -std=c++17")
set(WM_CFLAGS ${WM_CXXFLAGS})

###### source env vars
set(LIB_SRC "${WM_PROJECT_DIR}/src")


##### Run env vars
set(FOAM_SRC ${WM_PROJECT_DIR}/src)

set(FOAM_APP ${WM_PROJECT_DIR}/applications)
set(FOAM_MODULES ${FOAM_APP}/modules)
set(FOAM_SOLVERS ${FOAM_APP}/solvers)
set(FOAM_UTILITIES ${FOAM_APP}/utilities)
set(FOAM_LIBBIN  ${CMAKE_INSTALL_PREFIX}/lib)
set(FOAM_APPBIN  ${CMAKE_INSTALL_PREFIX}/bin)

#include(${CMAKE_CURRENT_LIST_DIR}/write_env_file.cmake)

#write_setup_env_file(
#    FILE ${env_file}
#    EXPORT_VARS
#        WM_PROJECT_DIR
#        WM_PROJECT
#        WM_PROJECT_VERSION
#        WM_PROJECT_INST_DIR
#        WM_PROJECT_USER_DIR
#        WM_THIRD_PARTY_DIR
#        WM_ARCH
#        WM_ARCH_OPTION
#        WM_DIR
#        WM_LABEL_SIZE
#        WM_LABEL_OPTION
#        WM_LINK_LANGUAGE
#        WM_MPLIB
#        WM_OPTIONS
#        WM_PRECISION_OPTION
#        WM_CC
#        WM_CFLAGS
#        WM_CXX
#        WM_CXXFLAGS
#        WM_COMPILER
#        WM_COMPILE_OPTION
#        WM_COMPILER_LIB_ARCH
#        WM_COMPILER_TYPE
#        WM_LDFLAGS
#        WM_LINK_LANGUAGE
#        WM_OSTYPE
#
#        LIB_SRC
#        FOAM_SRC
#        FOAM_APP
#        FOAM_MODULES
#        FOAM_SOLVERS
#        FOAM_UTILITIES
#        FOAM_LIBBIN
#        FOAM_APPBIN
#        FOAM_USER_APPBIN
#        FOAM_MPI
#
#        FOAM_SIGFPE
#        FOAM_SETNAN
#)

set(env_file ${CMAKE_BINARY_DIR}/FOAMenv.sh)
configure_file(${CMAKE_CURRENT_LIST_DIR}/FOAMenv.sh.in ${env_file} @ONLY)

install(FILES ${env_file}
    DESTINATION .
)
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

set(WM_OPTIONS "${WM_ARCH}${WM_COMPILER}${WM_PRECISION_OPT}${WM_COMPILE_OPTION}")
message(STATUS "WM_OPTIONS = ${WM_OPTIONS}")

###### source env vars
set(LIB_SRC "${WM_PROJECT_DIR}/src")


##### Run env vars
set(FOAM_APP ${WM_PROJECT_DIR}/applications)
set(FOAM_SOLVERS ${FOAM_APP}/solvers)
set(FOAM_SRC ${WM_PROJECT_DIR}/src)

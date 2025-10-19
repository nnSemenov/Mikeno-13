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
)

target_compile_options(OpenFOAM_Defines INTERFACE
#    -Wall
#    -Wextra
#    -Wold-style-cast
#    -Wnon-virtual-dtor
#    -Wno-unused-parameter
#    -Wno-invalid-offsetof
#    -Wno-undefined-var-template
#    -Wno-unqualified-std-cast-call

# less warn
    -Wno-old-style-cast
    -Wno-unused-local-typedefs
    -Wno-tautological-undefined-compare
    -Wno-shift-negative-value
)
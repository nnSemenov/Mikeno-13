
target_compile_options(OpenFOAM_Defines INTERFACE
    -Wall
    -Wextra
    -Wold-style-cast
    -Wnon-virtual-dtor
    -Wno-unused-parameter
    -Wno-invalid-offsetof
    -Wno-attributes
    -ftemplate-depth-256

    -frounding-math
    -ftrapping-math
)


list(APPEND Mikeno_less_warn_options
    -Wno-old-style-cast
    -Wno-unused-local-typedefs
    -Wno-tautological-undefined-compare
    -Wno-shift-negative-value
)

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
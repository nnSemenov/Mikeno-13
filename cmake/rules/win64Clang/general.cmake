
target_compile_options(OpenFOAM_Defines INTERFACE
    -Wno-unsafe-buffer-usage
#    -Wall
#    -Wextra
#    -Wold-style-cast
#    -Wnon-virtual-dtor
#    -Wno-unused-parameter
#    -Wno-invalid-offsetof
#    -Wno-undefined-var-template
#    -Wno-unqualified-std-cast-call

#    -Wpre-c++17-compat
#    -Wc++98-compat
#    -Wunsafe-buffer-usage
#    -Wextra-semi
#    -fsafe-buffer-usage-suggestions
#    -ftemplate-depth-256

    /fp:except
#    -ffp-exception-behavior=maytrap
)

list(APPEND Mikeno_less_warn_options
        -Wno-old-style-cast
        -Wno-unused-local-typedefs
        -Wno-tautological-undefined-compare
        -Wno-shift-negative-value
)
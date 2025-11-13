lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name chemkinToFoam)

flex_target(chemkinToFoamFlex 
    chemkinReader/chemkinLexer.L
    chemkinReader/chemkinLexer.L.C
    COMPILE_FLAGS "-+ -f"
)

add_executable(${target_name}
    chemkinReader/chemkinReader.C
    # chemkinReader/chemkinLexer.L
    chemkinToFoam.C
    ${FLEX_chemkinToFoamFlex_OUTPUTS}
)

target_include_directories(${target_name} PRIVATE
    lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OSspecific
    OpenFOAM

    chemistryModel
    specie
    genericFields
    genericFvFields
    Pstream_best
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=libNULL.so
)

set(FOAM_regular_executables "${FOAM_regular_executables};${target_name}" PARENT_SCOPE)
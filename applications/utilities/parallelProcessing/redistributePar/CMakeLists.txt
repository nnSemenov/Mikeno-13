lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name redistributePar)

add_executable(${target_name}
    loadOrCreateMesh.C
    redistributePar.C
)

target_include_directories(${target_name} PRIVATE
    lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OSspecific
    OpenFOAM

    finiteVolume 
    genericFvFields 
    decompositionMethods 
    meshTools 
    polyTopoChange 
    Pstream_best
)
set(optional_deps scotchDecomp ptscotchDecomp)
foreach(dep ${optional_deps})
    if(TARGET ${dep})
        target_link_libraries(${target_name} PRIVATE ${dep})
    endif()
endforeach()


target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=libNULL.so
)

set(FOAM_regular_executables "${FOAM_regular_executables};${target_name}" PARENT_SCOPE)
lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name renumberMesh)

add_executable(${target_name}
    renumberMesh.C
)

target_include_directories(${target_name} PRIVATE
    lnInclude
)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OSspecific
    OpenFOAM

    meshTools 
    polyTopoChange 
    finiteVolume 
    genericFvFields 
    renumberMethods 
    Pstream_best
    decompositionMethods
)

set(possible_dep metisDecomp scotchDecomp)
foreach(dep ${possible_dep})
    if(TARGET ${dep})
        target_link_libraries(${target_name} PRIVATE
            ${dep}
        )
    endif()
    
endforeach()


target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=libNULL.so
)

set(FOAM_regular_executables "${FOAM_regular_executables};${target_name}" PARENT_SCOPE)
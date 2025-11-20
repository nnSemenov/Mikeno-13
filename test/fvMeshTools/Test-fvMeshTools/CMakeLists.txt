cmake_minimum_required(VERSION 3.28)
project(test_find_Mikeno LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Mikeno CONFIG REQUIRED)

add_executable(Test-fvMeshTools Test-fvMeshTools.C)

target_link_libraries(Test-fvMeshTools PRIVATE
    Mikeno::OpenFOAM_Defines
    Mikeno::OpenFOAM
    Mikeno::OSspecific

    Mikeno::polyTopoChange
    Mikeno::meshTools
    Mikeno::finiteVolume
    Mikeno::genericFvFields
)
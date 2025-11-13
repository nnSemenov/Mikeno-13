cmake_minimum_required(VERSION 3.28)
project(test_find_Mikeno LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Mikeno CONFIG REQUIRED)

message(STATUS "special libs: ${FOAM_special_libraries}")
message(STATUS "regular libs: ${FOAM_regular_libraries}")

get_target_property(lib_foam_loc Mikeno::OpenFOAM LOCATION)
message(STATUS "Location of libOpenFOAM: ${lib_foam_loc}")

get_target_property(foam_include_dir Mikeno::OpenFOAM INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "Mikeno::OpenFOAM include dir: ${foam_include_dir}")

add_executable(test_foam test_foam.cpp)
target_link_libraries(test_foam PRIVATE
    Mikeno::OpenFOAM_Defines
    Mikeno::OpenFOAM
    Mikeno::OSspecific
)
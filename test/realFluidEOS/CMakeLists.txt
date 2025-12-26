cmake_minimum_required(VERSION 3.28)
project(test-realFluidEOS LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Mikeno CONFIG REQUIRED)

include(rapidcsv.cmake)

add_executable(Test-cubicEOS Test-cubicEOS.C)

target_include_directories(Test-cubicEOS PRIVATE
    $ENV{LIB_SRC}/physicalProperties/lnInclude 
    $ENV{LIB_SRC}/thermophysicalModels/basic/lnInclude 
    $ENV{LIB_SRC}/MomentumTransportModels/momentumTransportModels/lnInclude 
    $ENV{LIB_SRC}/MomentumTransportModels/compressible/lnInclude 
    $ENV{LIB_SRC}/thermophysicalModels/multicomponentThermo/lnInclude 
    $ENV{LIB_SRC}/ThermophysicalTransportModels/fluidMulticomponentThermo/lnInclude
)

target_link_libraries(Test-cubicEOS PRIVATE
    Mikeno::OpenFOAM_Defines
    Mikeno::OSspecific
    Mikeno::OpenFOAM

    Mikeno::finiteVolume
    Mikeno::fvModels
    Mikeno::fvConstraints
    Mikeno::meshTools
    Mikeno::specie
    Mikeno::fluidThermophysicalModels
    Mikeno::momentumTransportModels
    Mikeno::compressibleMomentumTransportModels
    Mikeno::multicomponentThermophysicalModels

    rapidcsv
)
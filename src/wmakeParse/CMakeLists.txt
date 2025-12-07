lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name wmakeParse)

add_library(${target_name} SHARED
    parse_wmake.H
    parse_wmake.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_include_directories(${target_name} PRIVATE

)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    Boost::regex
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

target_compile_features(${target_name} PRIVATE
    cxx_std_23
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)


add_executable(test_wmakeParse test.cpp)
target_link_libraries(test_wmakeParse PRIVATE wmakeParse)
target_compile_features(test_wmakeParse PRIVATE
    cxx_std_23
)
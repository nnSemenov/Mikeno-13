lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

add_library(tracking SHARED
    tracking.C
)
target_include_directories(tracking PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_link_libraries(tracking PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    meshTools
)

target_compile_definitions(tracking PRIVATE
    LIB_NAME=libtracking.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};tracking" PARENT_SCOPE)



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

install(TARGETS tracking
    DESTINATION lib
)
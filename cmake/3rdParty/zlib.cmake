find_package(ZLIB REQUIRED)

if(NOT TARGET ZLIB::ZLIB)
    message(WARNING "no zlib target ZLIB::ZLIB")
endif ()
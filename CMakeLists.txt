cmake_minimum_required(VERSION 3.15)
project(QRCodeLib VERSION 1.0.0 LANGUAGES CXX)

# Dépendances : pkg-config, qrencode, libpng
find_package(PkgConfig REQUIRED)
pkg_check_modules(QRENCODE REQUIRED IMPORTED_TARGET qrencode)
find_package(PNG REQUIRED)

# Bibliothèque QRCodeLib
add_library(QRCodeLib src/QRCodeGenerator.cpp)
target_include_directories(QRCodeLib
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${QRENCODE_INCLUDE_DIRS}
        ${PNG_INCLUDE_DIRS}
)
target_link_libraries(QRCodeLib
        PUBLIC
        PkgConfig::QRENCODE
        PNG::PNG
)

# Exécutable d'exemple
add_executable(QRCodeExample example/main.cpp)
target_link_libraries(QRCodeExample PRIVATE QRCodeLib)
target_include_directories(QRCodeExample PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Installation (optionnel)
install(TARGETS QRCodeLib DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

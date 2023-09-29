cmake_minimum_required(VERSION 3.23)
project(Lab2_grafica)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

set(SDL2_PATH "C:/Users/acer/OneDrive - Universidad del Valle de Guatemala/Documentos/uvg/SDL2-2.28.2/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})


add_executable(Lab2_grafica main.cpp)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})

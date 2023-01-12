cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 17)
project(Tetris VERSION 1.0.0 LANGUAGES CXX)

find_package(SFML 2.5 REQUIRED COMPONENTS graphics system window audio)
set(SFML_LIBS sfml-system sfml-window sfml-graphics sfml-audio)

include_directories(include)
file(GLOB SOURCES src/*.cpp include/*.h)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${SFML_LIBS})
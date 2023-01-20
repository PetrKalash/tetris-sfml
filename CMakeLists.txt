#-Configuration-#
cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME Tetris)
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

#-Add SFML-#
find_package(SFML 2.5 REQUIRED COMPONENTS graphics system window audio)
find_package(Threads REQUIRED)
set(SFML_LIBS sfml-system sfml-window sfml-graphics sfml-audio)

#-Enabling files-#
include_directories(include)
file(GLOB SOURCES src/*.cpp include/*.h)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${SFML_LIBS})

#-Copy files to the binary directory-#
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#-Connecting MSVC libraries-#
if(MSVC)
   foreach(lib ${SFML_LIBS})
      get_target_property(lib_path ${lib} LOCATION)
      file(COPY ${lib_path} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
   endforeach()
endif()
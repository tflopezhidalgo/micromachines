cmake_minimum_required(VERSION 3.13)
project(Testing)

set(CMAKE_CXX_STANDARD 11)

set(SFML_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SFML_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/lib)
set(SFML_DIR ${PROJECT_SOURCE_DIR}/lib/cmake/SFML)

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

add_subdirectory(Box2D)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.cpp")

add_executable(Testing ${sources})
# add_executable(Testing main.cpp Juego.cpp Car.cpp Tire.cpp Border.cpp ProccessContact.cpp)
target_link_libraries (Testing sfml-graphics sfml-window sfml-system)
target_link_libraries(Testing TG::Box2D)

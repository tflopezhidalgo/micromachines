cmake_minimum_required(VERSION 3.9)
project(Micromachines)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-ggdb -DDebug -fno-inline -O3")    # Flags de la cátedra
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

include_directories(${PROJECT_SOURCE_DIR}/src/client)
include_directories(${PROJECT_SOURCE_DIR}/src/server)
include_directories(${PROJECT_SOURCE_DIR}/src/common)

file(GLOB SERVER_SRC_FILES "src/server/*.cpp")
file(GLOB COMMON_SRC_FILES "src/common/*.cpp")
file(GLOB CLIENT_SRC_FILES "src/client/*.cpp")

set(SOURCE CMAKE_SOURCE_DIR)

add_executable(Client src/client/main.cpp ${CLIENT_SRC_FILES} ${COMMON_SRC_FILES})
target_include_directories(Client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
#target_link_libraries(Client SDL2 SDL2_image)
target_link_libraries(Client -pthread)

add_executable(Server src/server/main.cpp ${SERVER_SRC_FILES} ${COMMON_SRC_FILES} src/server/ProtectedQueue.h)
target_include_directories(Server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Server -pthread)

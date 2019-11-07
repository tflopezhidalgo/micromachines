cmake_minimum_required(VERSION 3.9)
project(Micromachines)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-ggdb -DDebug -fno-inline -O3")    # Flags de la cátedra
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

include_directories(${PROJECT_SOURCE_DIR}/src/client)
include_directories(${PROJECT_SOURCE_DIR}/src/server)
include_directories(${PROJECT_SOURCE_DIR}/src/common)
include_directories(${PROJECT_SOURCE_DIR}/src/client/lua)

file(GLOB SERVER_SRC_FILES "src/server/*.cpp")
file(GLOB COMMON_SRC_FILES "src/common/*.cpp")
file(GLOB CLIENT_SRC_FILES "src/client/*.cpp")
file(GLOB ENTITIES_SRC_FILES "src/server/entities/*.cpp")
file(GLOB PLUGINS_SRC_FILES "src/server/plugins/*.cpp")
file(GLOB LUA_SRC_FILES "src/client/lua/*.cpp")

set(SOURCE CMAKE_SOURCE_DIR)

add_executable(Lua src/client/lua/main_lua.cpp ${LUA_SRC_FILES})

add_executable(Client src/client/main.cpp ${CLIENT_SRC_FILES} ${COMMON_SRC_FILES})
target_link_libraries(Client SDL2 SDL2_image pthread lua5.3)

add_executable(Server src/server/main.cpp ${SERVER_SRC_FILES} ${COMMON_SRC_FILES} ${ENTITIES_SRC_FILES} ${PLUGINS_SRC_FILES})
add_subdirectory(${PROJECT_SOURCE_DIR}/src/server ${PROJECT_SOURCE_DIR}/build/Box2D-build)
target_link_libraries(Server Box2D pthread)



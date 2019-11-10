cmake_minimum_required(VERSION 3.9)
project(Micromachines)

find_package(Lua REQUIRED)
find_package(Qt5Widgets REQUIRED)

message("LUA_FOUND: ${LUA_FOUND}")
message("LUA_LIBRARIES: ${LUA_INCLUDE_DIR}")
message("LUA_INCLUDE_DIR: ${LUA_INCLUDE_DIR}")
message("LUA_VERSION_STRING: ${LUA_VERSION_STRING}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS "-ggdb -DDebug -fno-inline -O3 -std=c++11")    # Flags de la cátedra
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

qt5_wrap_ui(UIS_HDRS ${PROJECT_SOURCE_DIR}/src/client/qt/*.ui)

include_directories(${LUA_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src/client)
include_directories(${PROJECT_SOURCE_DIR}/src/server)
include_directories(${PROJECT_SOURCE_DIR}/src/common)
include_directories(${PROJECT_SOURCE_DIR}/src/client/lua)
include_directories(${PROJECT_SOURCE_DIR}/src/client/qt)

file(GLOB SERVER_SRC_FILES "src/server/*.cpp")
file(GLOB COMMON_SRC_FILES "src/common/*.cpp")
file(GLOB CLIENT_SRC_FILES "src/client/*.cpp")
file(GLOB ENTITIES_SRC_FILES "src/server/entities/*.cpp")
file(GLOB PLUGINS_SRC_FILES "src/server/plugins/*.cpp")
file(GLOB LUA_SRC_FILES "src/client/lua/*.cpp")
file(GLOB QT_SRC_FILES "src/client/qt/.cpp")

set(SOURCE CMAKE_SOURCE_DIR)

add_executable(Client src/client/main.cpp ${CLIENT_SRC_FILES} ${COMMON_SRC_FILES} ${LUA_SRC_FILES} ${UIS_HDRS} src/client/qt/mainwindow.cpp )
target_link_libraries(Client SDL2 SDL2_image pthread lua5.3 m dl Qt5::Widgets)

add_executable(Server src/server/main.cpp ${SERVER_SRC_FILES} ${COMMON_SRC_FILES} ${ENTITIES_SRC_FILES} ${PLUGINS_SRC_FILES})
add_subdirectory(${PROJECT_SOURCE_DIR}/src/server ${PROJECT_SOURCE_DIR}/build/Box2D-build)
target_link_libraries(Server Box2D pthread dl)



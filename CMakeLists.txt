cmake_minimum_required(VERSION 3.9)
project(Micromachines)

find_package(Lua REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_BINARY_DIR build)
set(CMAKE_CXX_FLAGS "-ggdb -DDebug -fno-inline -O3 -std=c++11")    # Flags setting

qt5_wrap_ui(UIS_HDRS ${PROJECT_SOURCE_DIR}/src/client/qt/mainwindow.ui)

include_directories(${LUA_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src/server/model)
include_directories(${PROJECT_SOURCE_DIR}/src/server/matches-management)

include_directories(${PROJECT_SOURCE_DIR}/src/common)

include_directories(${PROJECT_SOURCE_DIR}/src/client)
include_directories(${PROJECT_SOURCE_DIR}/src/client/lua)
include_directories(${PROJECT_SOURCE_DIR}/src/client/qt)
include_directories(${PROJECT_SOURCE_DIR}/src/client/ffmpeg)
include_directories(${PROJECT_SOURCE_DIR}/build)

file(GLOB_RECURSE COMMON_SRC_FILES "src/common/*.cpp")
file(GLOB_RECURSE CLIENT_SRC_FILES "src/client/*.cpp")
file(GLOB MODEL_SRC_FILES "src/server/model/*.cpp")
file(GLOB MATCHES_MANAGEMENT_SRC_FILES "src/server/matches-management/*.cpp")
file(GLOB PLUGINS_MANAGEMENT_SRC_FILES "src/server/plugins-management/*.cpp")

install(DIRECTORY ${PROJECT_SOURCE_DIR}/src/client/lua DESTINATION ${CMAKE_BINARY_DIR})

# Client build
add_executable(Client src/client/main.cpp ${CLIENT_SRC_FILES} ${COMMON_SRC_FILES} ${UIS_HDRS})
target_link_libraries(Client SDL2 SDL2_image SDL2_ttf SDL2_mixer pthread lua5.3 m dl Qt5::Widgets avformat avcodec avutil swscale)

# Server build
add_executable(Server src/server/main.cpp ${MODEL_SRC_FILES} ${COMMON_SRC_FILES} ${PLUGINS_MANAGEMENT_SRC_FILES} ${MATCHES_MANAGEMENT_SRC_FILES})
target_link_libraries(Server Box2D pthread dl)

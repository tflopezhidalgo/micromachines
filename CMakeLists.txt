cmake_minimum_required(VERSION 3.9)
project(Micromachines)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)  # Tratar de evitar los flags globales, hacerlo por executable
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/build) #not neccesary yet
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)  # Crear sobre build los ejecutables
																 # (por algo se llama build)

include_directories(${PROJECT_SOURCE_DIR}/src/client)
include_directories(${PROJECT_SOURCE_DIR}/src/server)
include_directories(${PROJECT_SOURCE_DIR}/src/common)

<<<<<<< HEAD
set(SERVER_SRC_FILES
		common/Thread.cpp
		common/Socket.cpp
		common/SocketException.h
		server/Car.cpp
		server/Health.cpp
		#... put all server source
		server/LobbyClientAcceptor.cpp server/LobbyClientAcceptor.h server/LobbyClientOperator.cpp server/LobbyClientOperator.h server/LobbyGamesManager.cpp server/LobbyGamesManager.h server/Game.cpp server/Game.h)
=======
file(GLOB SERVER_SRC_FILES "src/server/*.cpp")
file(GLOB COMMON_SRC_FILES "src/common/*.cpp")
file(GLOB CLIENT_SRC_FILES "src/client/*.cpp")
>>>>>>> 94079a3d54f01a703b5fc84dd998c428c52a66fb

add_executable(Client src/client/main.cpp ${CLIENT_SRC_FILES} ${COMMON_SRC_FILES})
add_executable(Server src/server/main.cpp ${SERVER_SRC_FILES} ${COMMON_SRC_FILES})

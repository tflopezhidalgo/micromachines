cmake_minimum_required(VERSION 3.14)
project(Micromachines)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake) #not neccesary yet
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

include_directories(${PROJECT_SOURCE_DIR}/client)
include_directories(${PROJECT_SOURCE_DIR}/server)
include_directories(${PROJECT_SOURCE_DIR}/common)

set(SERVER_SRC_FILES
		common/Thread.cpp
		common/Socket.cpp
		common/SocketException.h
		server/Car.cpp
		server/Health.cpp
		#... put all server source
		server/LobbyClientAcceptor.cpp server/LobbyClientAcceptor.h server/LobbyClientOperator.cpp server/LobbyClientOperator.h server/LobbyGamesManager.cpp server/LobbyGamesManager.h server/Game.cpp server/Game.h)

set(CLIENT_SRC_FILES
		common/Thread.cpp
		common/Socket.cpp
		common/SocketException.h
		#... put all client source files
	)

add_executable(Client client/main.cpp ${CLIENT_SRC_FILES})
add_executable(Server server/main.cpp ${SERVER_SRC_FILES})

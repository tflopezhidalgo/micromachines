#!/bin/bash
sudo apt-get update && sudo apt-get install -y  libegl1-mesa-dev libgles2-mesa-dev libsdl2-dev libsdl2-image-dev nlohmann-json-dev lua5.3 liblua5.3-dev qt5-default libsdl2-mixer-dev libavutil-dev libswresample-dev libavformat-dev libavcodec-dev libswscale-dev libsdl2-ttf-dev

mkdir build
cd build
cmake ..
make

cp src/client/lua/*.lua build/

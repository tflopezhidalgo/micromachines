#!/bin/bash

echo "Installing dependencies..."

sudo apt-get update && sudo apt-get install $(cat requirements.txt) -y

echo "Done"

mkdir build
cd build
cmake ..
make

cp src/client/lua/*.lua build/


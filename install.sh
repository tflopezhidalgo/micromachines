#!/bin/bash

# Colores
GREEN="\033[1;32m"
YELLOW="\033[1;33m"
DEFAULT="\033[0m"

echo -e "${YELLOW}Instalando dependencias necesarias ... ${DEFAULT}"

sudo apt-get update && sudo apt-get install $(cat requirements.txt) -y

mkdir build
cd build
cmake ..
make

cp src/client/lua/*.lua build/

echo -e "${GREEN}Se ha generado correctamente la versión de Micromachines${DEFAULT}"

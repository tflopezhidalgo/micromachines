#!/bin/bash

# Colores
RED="\033[1;31m"
GREEN="\033[1;32m"
YELLOW="\033[1;33m"
DEFAULT="\033[0m"

echo -e "${YELLOW}Instalando dependencias necesarias ... ${DEFAULT}"

sudo apt-get update && sudo apt-get install $(cat requirements.txt) -y 

if [[ $? > 0 ]]
then
    echo -e "${RED}Ocurrió un error durante la instalación de las dependencias ${DEFAULT}"
    exit 1
fi

mkdir -p build && cd build && cmake .. && make

if [[ $? > 0 ]]
then
    echo -e "${RED}Ocurrió un error durante la compilación ${DEFAULT}"
    exit 1
fi

cp src/client/lua/*.lua build/

echo -e "${GREEN}Se ha generado correctamente la versión de Micromachines${DEFAULT}"

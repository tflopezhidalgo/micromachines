//
// Created by leobellaera on 28/10/19.
//

#include "ConfigMapBuilder.h"
#include "ConfigMapBuilderException.h"
#include <sstream>

#define DELIM_CHAR '='

#define OPENING_ERROR_MSG "An error occurred while\
 trying to open the config file.\n"

#define READING_ERROR_MSG "An error occurred while\
 trying to read the config file.\n"

ConfigMapBuilder::ConfigMapBuilder(const char* filePath) {
    file.exceptions(std::ifstream::badbit);
    file.open(filePath);
    if (!file.is_open()) {
        throw ConfigMapBuilderException(OPENING_ERROR_MSG);
    }
    try {
        this->buildMap();
    } catch (std::ios_base::failure& e) {
        throw ConfigMapBuilderException(READING_ERROR_MSG);
    }
}

void ConfigMapBuilder::buildMap() {
    while (!file.eof()) {
        std::string aux;
        std::string key;
        std::string value;

        std::getline(file, aux);
        std::istringstream line_stream(aux);

        std::getline(line_stream, key, DELIM_CHAR);
        std::getline(line_stream, value, DELIM_CHAR);

        float valueAsFloat = std::stof(value);
        config.emplace(key, valueAsFloat);
    }
}

std::map<std::string,float>& ConfigMapBuilder::getConfigMap(){
    return config;
}

ConfigMapBuilder::~ConfigMapBuilder() {}

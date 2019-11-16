#ifndef MICROMACHINES_CONFIGMAPBUILDER_H
#define MICROMACHINES_CONFIGMAPBUILDER_H

#include <map>
#include <string>
#include <fstream>

class ConfigMapBuilder {
private:
    std::map<std::string, float> config;
    std::ifstream file;
    void buildMap();
public:
    explicit ConfigMapBuilder(const char* filePath);
    std::map<std::string,float>& getConfigMap();
    ~ConfigMapBuilder();
};

#endif //MICROMACHINES_CONFIGMAPBUILDER_H

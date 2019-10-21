//
// Created by eliana on 20/10/19.
//

#ifndef MICROMACHINES_PLUGIN_H
#define MICROMACHINES_PLUGIN_H

enum PluginType {
    INCREASE_VELOCITY,
    DECREASE_VELOCITY
};

class Plugin {
public:
    Plugin* createPlugin(PluginType type, std::vector<std::string> cars, std::string mapa);
};


#endif //MICROMACHINES_PLUGIN_H

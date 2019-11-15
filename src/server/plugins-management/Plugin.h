//
// Created by eliana on 9/11/19.
//

#ifndef MICROMACHINES_PLUGIN_H
#define MICROMACHINES_PLUGIN_H

class Plugin {
public:
    Plugin() {}
    virtual void updateModel() = 0;
    virtual ~Plugin() {}
};

using PluginCreator = Plugin *(*)();

#endif //MICROMACHINES_PLUGIN_H

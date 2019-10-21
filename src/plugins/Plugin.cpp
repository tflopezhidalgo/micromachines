//
// Created by eliana on 20/10/19.
//

#include "Plugin.h"

Plugin* Plugin::createPlugin(PluginType type, std::vector<std::string> cars, std::string mapa) {
    switch (type) {
        case PluginType::INCREASE_VELOCITY:
            return Plugin_IncreaseVelocity(cars, mapa);
        case PluginType::DECREASE_VELOCITY:
            return Plugin_DecreaseVelocity(cars, mapa);
    }
}
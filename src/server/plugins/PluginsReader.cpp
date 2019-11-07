//
// Created by eliana on 7/11/19.
//

#include "PluginsReader.h"

void PluginsReader::dirReader() {
    DIR* dir;
    struct dirent *file;

    dir = opendir("plugins");
    if (dir != NULL) {
        while (file = readdir(dir)){
            std::cout << file->d_name << std::endl;
        }
    }
    closedir(dir);
}

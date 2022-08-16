//
// Created by newst on 2022-08-16.
//

#ifndef BODA_BASELOADER_H
#define BODA_BASELOADER_H

#include "BaseObject.h"
#include <vector>
#include <string_view>

class BaseLoader {
public:
    virtual bool loadFile(std::string_view path, std::vector<Position>& positions) = 0;
};


#endif //BODA_BASELOADER_H

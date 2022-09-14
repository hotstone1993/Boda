//
// Created by newst on 2022-08-16.
//

#ifndef BODA_OBJECTFILELOADER_H
#define BODA_OBJECTFILELOADER_H

#include "BaseLoader.h"

class ObjectFileLoader: public BaseLoader {
public:
    ObjectFileLoader();
    virtual ~ObjectFileLoader();

    bool loadFile(std::string_view path, BaseMesh& mesh) override;
};


#endif //BODA_OBJECTFILELOADER_H

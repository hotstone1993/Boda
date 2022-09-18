//
// Created by newst on 2022-08-14.
//

#ifndef BODA_OBJECTFACTORY_H
#define BODA_OBJECTFACTORY_H

#include "BoxObject.h"
#include "PlaneObject.h"

class ObjectFactory {
public:
    static std::unique_ptr<BaseObject> createObject(const ObjectType& type, size_t key) {
        if (type == ObjectType::BOX) {
            return std::make_unique<BoxObject>(key);
        } else if(type == ObjectType::PLANE) {
            return std::make_unique<PlaneObject>(key);
        } else {
            return std::make_unique<BoxObject>(key);
        }
    }
};


#endif //BODA_OBJECTFACTORY_H

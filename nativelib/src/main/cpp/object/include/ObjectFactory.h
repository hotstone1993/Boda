//
// Created by newst on 2022-08-14.
//

#ifndef BODA_OBJECTFACTORY_H
#define BODA_OBJECTFACTORY_H

#include "BoxObject.h"
#include "PlaneObject.h"

class ObjectFactory {
public:
    static std::unique_ptr<BaseObject> createObject(const ObjectType& type, unsigned int idx) {
        if (type == ObjectType::BOX) {
            return std::make_unique<BoxObject>(idx);
        } else if(type == ObjectType::PLANE) {
            return std::make_unique<PlaneObject>(idx);
        } else {
            return std::make_unique<BoxObject>(idx);
        }
    }
};


#endif //BODA_OBJECTFACTORY_H

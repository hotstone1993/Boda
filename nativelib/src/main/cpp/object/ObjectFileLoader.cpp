//
// Created by newst on 2022-08-16.
//

#include "include/ObjectFileLoader.h"
#include <charconv>

ObjectFileLoader::ObjectFileLoader() {

}

ObjectFileLoader::~ObjectFileLoader() {
}

void getPosition(std::string_view sv, Position& p) {
    unsigned int save = 0;
    int count = 0;
    char *end;

    for (unsigned int idx = 0; idx < sv.size(); ++idx ) {
        if (sv[idx] == ' ') {
            if (save != 0) {
                p.data[count++] = std::strtof(sv.data() + save, &end);
            }
            save = idx + 1;
        }
        else if (sv[idx] == '\n') {
            p.data[count++] = std::strtof(sv.data() + save, &end);
            break;
        }
    }
}

std::string_view getNewLine(std::string_view sv) {
    for (unsigned int idx = 0; idx < sv.size(); ++idx ) {
        if (sv[idx] == '\n') {
            return sv.substr(idx + 1, sv.size());
        }
    }
    return sv.substr();
}

bool ObjectFileLoader::loadFile(std::string_view sv, std::vector<Position>& positions) {
    std::string_view s = sv;
    Position p;

    if (sv.empty())
        return false;
    while (true) {
        s = getNewLine(s);

        if (s.empty())
            break;

        switch (s.front()) {
            case 'v': {
                getPosition(s, p);
                positions.emplace_back(p.data[0], p.data[1], p.data[2]);
                break;
            }
        }
    }
    return true;
}
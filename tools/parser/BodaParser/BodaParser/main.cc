#include <iostream>

#include "FBXParser.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        std::cout << "Please enter the file path\n";
    }
    if (FBXParser().createBSSFile("C:\\Users\\newst\\Downloads\\fbx\\Intergalactic_Spaceship.fbx")) {
        std::cout << "Fail to create BSS file.\n";
    } else {
        std::cout << "Success to create BSS file.\n";
    }

    return 0;
}
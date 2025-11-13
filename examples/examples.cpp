#include <iostream>
#include <string>
#include "examples.h"


int main(int argc, char* argv[]) {
    // Если есть аргумент командной строки, используем его
    if (argc > 1) {
        std::string demoName = argv[1];
        if (demoName == "spinningPrismDemo") {
            return spinningPrism::spinningPrismDemo();
        }
        else if (demoName == "dancingNeonCubesDemo") {
            return dancingNeonCubes::dancingNeonCubesDemo();
        }
        else if (demoName == "solarSystemDemo") {
            return solarSystem::solarSystemDemo();
        }
        else if (demoName == "materialsDemo") {
            return materials::materialsDemo();
        }
        else {
            std::cout << "Unknown demo: " << demoName << std::endl;
            return 1;
        }
    }
    
    // Иначе спросим пользователя
    std::cout << "Select demo (1 or 2, 3, 4): ";
    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1:
        return spinningPrism::spinningPrismDemo();
    case 2:
        return dancingNeonCubes::dancingNeonCubesDemo();
    case 3:
        return solarSystem::solarSystemDemo();
    case 4:
        return materials::materialsDemo();
    default:
        std::cout << "Invalid choice." << std::endl;
        return 1;
    }
}
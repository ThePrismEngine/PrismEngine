#include <iostream>
#include <string>
#include "examples.h"


int main(int argc, char* argv[]) {
    // Если есть аргумент командной строки, используем его
    if (argc > 1) {
        std::string demoName = argv[1];
        if (demoName == "demo1") {
            return dancingNeonCubesDemo();
        }
        else if (demoName == "demo2") {
            return demo1();
        }
        else {
            std::cout << "Unknown demo: " << demoName << std::endl;
            return 1;
        }
    }
    
    // Иначе спросим пользователя
    std::cout << "Select demo (1 or 2, 3): ";
    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1:
        return spinningPrismDemo();
    case 2:
        return dancingNeonCubesDemo();
    case 3:
        return solarSystemDemo();
    default:
        std::cout << "Invalid choice." << std::endl;
        return 1;
    }
}
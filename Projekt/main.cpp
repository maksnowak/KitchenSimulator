#include <iostream>

// Interface functions

void mainMenu() {
    std::cout << "Welcome to Kitchen Simulator!" << std::endl;
    std::cout << "1. New Simulation" << std::endl;
    std::cout << "2. Load Simulation" << std::endl;
    std::cout << "0. Exit" << std::endl;
}

enum class MenuChoice {
    Exit = 0,
    NewSimulation = 1,
    LoadSimulation = 2
};

MenuChoice getMenuChoice() {
    std::cout << "Enter your choice: ";
    int choice;
    std::cin >> choice;
    return static_cast<MenuChoice>(choice);
}

int main() {
    mainMenu();
    MenuChoice user_choice = getMenuChoice();
    if (user_choice == MenuChoice::Exit) {
        std::cout << "Exiting..." << std::endl;
        return 0;
    }
    else if (user_choice == MenuChoice::NewSimulation) {
        std::cout << "Creating new simulation..." << std::endl;
    }
    else if (user_choice == MenuChoice::LoadSimulation) {
        std::cout << "Enter the file path to a saved simulation: " << std::endl;
        // TODO: Load simulation from JSON file
    }
    else {
        std::cout << "Invalid choice!" << std::endl;
    }
}
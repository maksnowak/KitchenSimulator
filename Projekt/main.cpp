#include <iostream>
#include <vector>
#include <iomanip>
#include "kitchen.h"
#include "recipe.h"
#include "ingredient.h"
#include "device.h"
#include "time.h"

// Interface functions

// Launching the program

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

// Simulation interface

void actionMenu() {
    std::cout << "1. Cook" << std::endl;
    std::cout << "2. New recipe" << std::endl;
    std::cout << "3. See recipes" << std::endl;
    std::cout << "4. See ingredients" << std::endl;
    std::cout << "5. See devices" << std::endl;
    std::cout << "6. Buy an ingredient" << std::endl;
    std::cout << "7. Buy a new device" << std::endl;
    std::cout << "8. Clean all devices" << std::endl;
    std::cout << "9. Take a break" << std::endl;
    std::cout << "0. End the day" << std::endl;
}

enum class ActionChoice {
    Cook = 1,
    NewRecipe = 2,
    SeeRecipes = 3,
    SeeIngredients = 4,
    SeeDevices = 5,
    BuyIngredient = 6,
    BuyDevice = 7,
    CleanDevices = 8,
    TakeBreak = 9,
    EndDay = 0
};

ActionChoice getActionChoice() {
    std::cout << "Enter your choice: ";
    int choice;
    std::cin >> choice;
    return static_cast<ActionChoice>(choice);
}

void endOfDayMenu() {
    std::cout << "You have finished the day" << std::endl;
    std::cout << "Would you like to save the simulation?" << std::endl;
    std::cout << "1. Yes" << std::endl;
    std::cout << "2. No" << std::endl;
}

enum class EndDayChoice {
    Yes = 1,
    No = 2
};

EndDayChoice getEndDayChoice() {
    std::cout << "Enter your choice: ";
    int choice;
    std::cin >> choice;
    return static_cast<EndDayChoice>(choice);
}

int main() {
    while (true) {
        mainMenu();
        MenuChoice user_choice = getMenuChoice();
        if (user_choice == MenuChoice::Exit) {
            std::cout << "Exiting..." << std::endl;
            break;
        } else if (user_choice == MenuChoice::NewSimulation) {
            while (true) {
                std::cout << "Creating new simulation..." << std::endl;
                Kitchen simulation(Time(8, 0), std::vector<Recipe>(), std::vector<Ingredient>(), std::vector<Device>());
                std::cout << "Done!" << std::endl;
                std::cout << "Current time: ";
                std::cout << std::setfill('0') << std::setw(2) << simulation.getTime().getHour();
                std::cout << ":";
                std::cout << std::setfill('0') << std::setw(2) << simulation.getTime().getMinute() << std::endl;
                actionMenu();
                ActionChoice action_choice = getActionChoice();
                // TODO: Implement actions
                if (action_choice == ActionChoice::EndDay) {
                    while (true) {
                        endOfDayMenu();
                        EndDayChoice end_day_choice = getEndDayChoice();
                        if (end_day_choice == EndDayChoice::Yes) {
                            std::cout << "Enter the file path to save the simulation: " << std::endl;
                            // TODO: Save simulation to JSON file
                            break;
                        } else if (end_day_choice == EndDayChoice::No) {
                            std::cout << "Exiting..." << std::endl;
                            break;
                        } else {
                            std::cout << "Invalid choice!" << std::endl;
                            continue;
                        }
                    }
                    break;
                }
            }
        } else if (user_choice == MenuChoice::LoadSimulation) {
            std::cout << "Enter the file path to a saved simulation: " << std::endl;
            // TODO: Load simulation from JSON file
            break;
        } else {
            std::cout << "Invalid choice!" << std::endl;
            continue;
        }
    }
    return 0;
}
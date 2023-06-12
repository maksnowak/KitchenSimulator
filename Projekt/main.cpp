#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "json.hpp"
#include "kitchen.h"

using json = nlohmann::json;
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

// Cooking interface

void cookMenu(Kitchen& simulation) {
    if (simulation.getRecipes().size() == 0) {
        std::cout << "You don't have any recipes!" << std::endl;
    }
    else {
        std::cout << "Choose a recipe to cook: " << std::endl;
        for (unsigned long i = 0; i < simulation.getRecipes().size(); i++) {
            std::cout << i + 1 << ". " << simulation.getRecipes()[i].getName() << std::endl;
        }
        int choice;
        std::cin >> choice;
        try {
            simulation.cook(simulation.getRecipes()[choice - 1]);
            std::cout << "Cooked " << simulation.getRecipes()[choice - 1].getName() << "!" << std::endl;
            std::cout << "Time elapsed: " << simulation.getRecipes()[choice -1].getTime() << " minutes" << std::endl;
        }
        catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
}

int main() {
    while (true) {
        mainMenu();
        MenuChoice user_choice = getMenuChoice();
        if (user_choice == MenuChoice::Exit) {
            std::cout << "Exiting..." << std::endl;
            break;
        } else if (user_choice == MenuChoice::NewSimulation) {
            std::cout << "Creating new simulation..." << std::endl;
            Kitchen simulation(Time(8, 0), std::vector<Recipe>(), std::vector<Ingredient>(), std::vector<Device>());
            std::cout << "Done!" << std::endl;
            while (true) {
                std::cout << "Current time: ";
                std::cout << std::setfill('0') << std::setw(2) << simulation.getTime().getHour();
                std::cout << ":";
                std::cout << std::setfill('0') << std::setw(2) << simulation.getTime().getMinute() << std::endl;
                actionMenu();
                ActionChoice action_choice = getActionChoice();
                if (action_choice == ActionChoice::Cook) {
                    cookMenu(simulation);
                    continue;
                }
                else if (action_choice == ActionChoice::EndDay) {
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
                else {
                    std::cout << "Invalid choice!" << std::endl;
                    continue;
                }
            }
        } else if (user_choice == MenuChoice::LoadSimulation) {
            std::cout << "Enter the file path to a saved simulation: " << std::endl;
            std::string user_input;
            std::cin >> user_input;
            std::cout << "Starting simulation..." << std::endl;
            std::ifstream file(user_input);
            json jsonData;

            if (file.is_open()) {
                file >> jsonData;

                uint hour = jsonData["Time"]["hour"];
                uint min = jsonData["Time"]["min"];
                Time time = Time(hour, min);

                json recipes = jsonData["Recipies"];
                std::vector<Recipe> recipe_list;

                for (const auto& recipe : recipes) {
                    std::string name = recipe["Name"];
                    // uint recipe_time = jsonData["Time"];         //dostaje objekt zamias liczby
                    std::string difficulty = recipe["Difficulty"];      //TODO: zamienic na enum difficulty

                    json ingredients = recipe["Ingredients"];
                    std::vector<Ingredient> recipe_ingredients;
                    for (const auto& ingredient : ingredients) {
                        std::string ingredientName = ingredient["Name"];
                        std::string ingredientType = ingredient["Type"];        //TODO: zamienic na enum ingedientType
                        uint calories = ingredient["Calories"];
                        recipe_ingredients.push_back(Ingredient(ingredientName, IngredientType::dairy, calories));
                    }

                    json devices = recipe["Devices"];
                    std::vector<Device> recipe_devices;
                    for (const auto& device : devices) {
                        std::string deviceName = device["Name"];
                        recipe_devices.push_back(Device(deviceName, State::clean));
                    }
                    recipe_list.push_back(Recipe(name, 10, Difficulty::easy, recipe_ingredients, recipe_devices));
                }

                json ingredients = jsonData["Ingredients"];
                std::vector<Ingredient> ingredient_list;
                for (const auto& ingredient : ingredients) {
                    std::string name = ingredient["Name"];
                    IngredientType type = ingredient["Type"];
                    uint calories = ingredient["Calories"];
                    ingredient_list.push_back(Ingredient(name, type, calories));
                }

                json devices = jsonData["Devices"];
                std::vector<Device> device_list;
                for (const auto& device : devices) {
                    std::string name = device["Name"];
                    std::string state = device["State"];
                    device_list.push_back(Device(name, State::clean));
                }

                Kitchen kitchen = Kitchen(time, recipe_list, ingredient_list, device_list);
                std::cout << "Simulation loaded successfully!" << std::endl;

            } else {
                std::cout << "Failed to open the file." << std::endl;
            }
            break;
        } else {
            std::cout << "Invalid choice!" << std::endl;
            continue;
        }
    }
    return 0;
}
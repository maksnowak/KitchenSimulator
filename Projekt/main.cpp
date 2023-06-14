#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "json.hpp"
#include "kitchen.h"
#include "time.h"
#include "recipe.h"
#include "ingredient.h"
#include "device.h"
#include "missing_ingredients_exception.h"
#include "missing_devices_exception.h"
#include "dirty_device_exception.h"


using json = nlohmann::json;

void validate(uint& variable) {
    while (true) {
        std::cin >> variable;
        if (variable > 0)
            break;
        else {
            std::cout << "Invalid input! Please enter a valid value: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

// Interface functions

auto to_ingredient_type(std::string type) {
    std::transform(type.begin(), type.end(), type.begin(), ::tolower);
    if (type == "meat") {
        return IngredientType::meat;
    } else if (type == "vegetable") {
        return IngredientType::vegetable;
    } else if (type == "fruit") {
        return IngredientType::fruit;
    } else if (type == "grain") {
        return IngredientType::grain;
    } else if (type == "dairy") {
        return IngredientType::dairy;
    } else if (type == "seasoning") {
        return IngredientType::seasoning;
    } else if (type == "other") {
        return IngredientType::other;
    } else {
        throw std::invalid_argument("Invalid ingredient type!");
    }
}

auto to_difficulty(std::string difficulty) {
    std::transform(difficulty.begin(), difficulty.end(), difficulty.begin(), ::tolower);
    if (difficulty == "easy") {
        return Difficulty::easy;
    } else if (difficulty == "medium") {
        return Difficulty::medium;
    } else if (difficulty == "hard") {
        return Difficulty::hard;
    } else {
        throw std::invalid_argument("Invalid difficulty!");
    }
}

auto to_state(std::string state) {
    std::transform(state.begin(), state.end(), state.begin(), ::tolower);
    if (state == "clean") {
        return State::clean;
    } else if (state == "dirty") {
        return State::dirty;
    } else {
        throw std::invalid_argument("Invalid state!");
    }
}

std::string type_to_string(IngredientType type) {
    if (type == IngredientType::meat) {
        return "meat";
    } else if (type == IngredientType::vegetable) {
        return "vegetable";
    } else if (type == IngredientType::fruit) {
        return "fruit";
    } else if (type == IngredientType::grain) {
        return "grain";
    } else if (type == IngredientType::dairy) {
        return "dairy";
    } else if (type == IngredientType::seasoning) {
        return "seasoning";
    } else if (type == IngredientType::other) {
        return "other";
    } else {
        throw std::invalid_argument("Invalid ingredient type!");
    }
}

std::string difficulty_to_string(Difficulty difficulty) {
    if (difficulty == Difficulty::easy) {
        return "easy";
    } else if (difficulty == Difficulty::medium) {
        return "medium";
    } else if (difficulty == Difficulty::hard) {
        return "hard";
    } else {
        throw std::invalid_argument("Invalid difficulty!");
    }
}

std::string state_to_string(State state) {
    if (state == State::clean) {
        return "clean";
    } else if (state == State::dirty) {
        return "dirty";
    } else {
        throw std::invalid_argument("Invalid state!");
    }
}

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
    std::cout << "0. Exit the simulation" << std::endl;
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

void exitSimulationMenu() {
    std::cout << "Would you like to save the simulation?" << std::endl;
    std::cout << "1. Yes" << std::endl;
    std::cout << "2. No" << std::endl;
}

enum class exitSimulationChoice {
    Yes = 1,
    No = 2
};

exitSimulationChoice getEndDayChoice() {
    std::cout << "Enter your choice: ";
    int choice;
    std::cin >> choice;
    return static_cast<exitSimulationChoice>(choice);
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

// New recipe interface

void newRecipeMenu(Kitchen& simulation) {
    if (simulation.getIngredients().size() == 0)
        std::cout << "You cannot make a recipe without ingredients!" << std::endl;
    else {
        std::cout << "Enter the name of the recipe: ";
        std::string name;
        std::getline(std::cin >> std::ws, name);
        std::cout << "How long does it take to cook the recipe? (in minutes): ";
        unsigned int time;
        validate(time);
        std::cout << "What is the difficulty of the recipe? (easy, medium, hard): ";
        std::string difficulty;
        std::cin >> difficulty;
        std::cout << "Which ingredient does the recipe use? (enter the number): " << std::endl;
        char all_added_ingredients_choice = 'n';
        std::vector<Ingredient> ingredients;
        do {
            for (unsigned long i = 0; i < simulation.getIngredients().size(); i++) {
                std::cout << i + 1 << ". " << simulation.getIngredients()[i].getName() << std::endl;
            }
            unsigned int choice;
            std::cin >> choice;
            if (std::find(ingredients.begin(), ingredients.end(), simulation.getIngredients()[choice - 1]) != ingredients.end())
                std::cout << "You have already added this ingredient!" << std::endl;
            else {
                try {
                    ingredients.push_back(simulation.getIngredients()[choice - 1]);
                }
                catch (std::exception& e) {
                    std::cout << e.what() << std::endl;
                }
            }
            std::cout << "Would you like to add another ingredient? (y/n): ";
            std::cin >> all_added_ingredients_choice;
        } while (all_added_ingredients_choice == 'y');
        std::vector<Device> devices;
        if (simulation.getDevices().size() != 0) {
            //TODO: you should be able to make a recipe without a device too
            std::cout << "Which device does the recipe use? (enter the number): " << std::endl;
            char all_added_devices_choice = 'n';
            do {
                for (unsigned long i = 0; i < simulation.getDevices().size(); i++) {
                    std::cout << i + 1 << ". " << simulation.getDevices()[i].getName() << std::endl;
                }
                unsigned int choice;
                validate(choice);
                if (std::find(devices.begin(), devices.end(), simulation.getDevices()[choice - 1]) != devices.end())
                    std::cout << "You have already added this device!" << std::endl;
                else
                    try {
                        devices.push_back(simulation.getDevices()[choice - 1]);
                    }
                    catch (std::exception& e) {
                        std::cout << e.what() << std::endl;
                    }
                std::cout << "Would you like to add another device? (y/n): ";
                std::cin >> all_added_devices_choice;
            } while (all_added_devices_choice == 'y');
        }
        try {
            simulation.addRecipe(Recipe(name, time, to_difficulty(difficulty), ingredients, devices));
            std::cout << "Added recipe " << name << "!" << std::endl;
        }
        catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
}

// All recipes interface

void seeRecipesMenu(Kitchen& simulation) {
    if (simulation.getRecipes().size() == 0)
        std::cout << "You don't have any recipes!" << std::endl;
    else {
        std::cout << "Your recipes: " << std::endl;
        for (unsigned long i = 0; i < simulation.getRecipes().size(); i++) {
            std::cout << simulation.getRecipes()[i].getName() << std::endl;
            std::cout << "Difficulty: " << difficulty_to_string(simulation.getRecipes()[i].getDifficulty()) << std::endl;
            std::cout << "Time: " << simulation.getRecipes()[i].getTime() << " minutes" << std::endl;
            std::cout << "Ingredients: " << std::endl;
            for (unsigned long j = 0; j < simulation.getRecipes()[i].getIngredients().size(); j++) {
                std::cout << "\t" << simulation.getRecipes()[i].getIngredients()[j].getName() << std::endl;
            }
            std::cout << "Devices: " << std::endl;
            for (unsigned long j = 0; j < simulation.getRecipes()[i].getDevices().size(); j++) {
                std::cout << "\t" << simulation.getRecipes()[i].getDevices()[j].getName() << std::endl;
            }
            std::cout << "Caloric value: " << simulation.getRecipes()[i].caloricValue() << std::endl;
            std::cout << std::endl;
        }
    }
}

// All ingredients interface

void seeIngredientsMenu(Kitchen& simulation) {
    if (simulation.getIngredients().size() == 0)
        std::cout << "You don't have any ingredients!" << std::endl;
    else {
        std::cout << "Your ingredients: " << std::endl;
        for (unsigned long i = 0; i < simulation.getIngredients().size(); i++) {
            std::cout << simulation.getIngredients()[i].getName() << std::endl;
            std::cout << "Type: " << type_to_string(simulation.getIngredients()[i].getType()) << std::endl;
            std::cout << "Calories: " << simulation.getIngredients()[i].getCalories() << std::endl;
            std::cout << std::endl;
        }
    }
}

// All devices interface

void seeDevicesMenu(Kitchen& simulation) {
    if (simulation.getDevices().size() == 0)
        std::cout << "You don't have any devices!" << std::endl;
    else {
        std::cout << "Your devices: " << std::endl;
        for (unsigned long i = 0; i < simulation.getDevices().size(); i++) {
            std::cout << simulation.getDevices()[i].getName() << std::endl;
            std::cout << "State: " << state_to_string(simulation.getDevices()[i].getState()) << std::endl;
            std::cout << std::endl;
        }
    }
}

// Buying ingredients interface

void buyIngredientMenu(Kitchen& simulation) {
    std::cout << "Enter the ingredients name: ";
    std::string name;
    std::getline(std::cin >> std::ws, name);
    std::cout << "Enter the ingredient's type: (meat, vegetable, fruit, grain, dairy, seasoning, other): ";
    std::string type;
    std::cin >> type;
    std::cout << "Enter the ingredient's calories: ";
    unsigned int calories;
    validate(calories);
    try {
        simulation.buyIngredient(Ingredient(name, to_ingredient_type(type), calories));
        std::cout << "Added ingredient " << name << "!" << std::endl;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void buyDeviceMenu(Kitchen& simulation) {
    std::cout << "Enter the device's name: ";
    std::string name;
    std::getline(std::cin >> std::ws, name);
    Device device = Device(name, State::clean);

    if (std::find(simulation.getDevices().begin(), simulation.getDevices().end(), device) != simulation.getDevices().end())
        std::cout << "You already have this device!" << std::endl;
    else {
        simulation.buyDevice(device);
        std::cout << "Added device " << name << "!" << std::endl;
    }
}

// Cleaning devices interface

void cleanDeviceMenu(Kitchen& simulation) {
    simulation.cleanDevices();
    std::cout << "Cleaned all devices!" << std::endl;
}

// Taking a break interface

void takeBreakMenu(Kitchen& simulation) {
    std::cout << "How long do you want to take a break for? (in minutes): ";
    unsigned int minutes;
    validate(minutes);
    simulation.takeBreak(minutes);
    std::cout << "Took a break for " << minutes << " minutes!" << std::endl;
}

// Main interface

void simulationInterface(Kitchen& simulation) {
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
        else if (action_choice == ActionChoice::NewRecipe) {
            newRecipeMenu(simulation);
            continue;
        }
        else if (action_choice == ActionChoice::SeeRecipes) {
            seeRecipesMenu(simulation);
            continue;
        }
        else if (action_choice == ActionChoice::SeeIngredients) {
            seeIngredientsMenu(simulation);
            continue;
        }
        else if (action_choice == ActionChoice::SeeDevices) {
            seeDevicesMenu(simulation);
            continue;
        }
        else if (action_choice == ActionChoice::BuyIngredient) {
            buyIngredientMenu(simulation);
            continue;
        }
        else if (action_choice == ActionChoice::BuyDevice) {
            buyDeviceMenu(simulation);
            continue;
        }
        else if (action_choice == ActionChoice::CleanDevices) {
            cleanDeviceMenu(simulation);
            continue;
        }
        else if (action_choice == ActionChoice::TakeBreak) {
            takeBreakMenu(simulation);
            continue;
        }
        else if (action_choice == ActionChoice::EndDay) {
            while (true) {
                exitSimulationMenu();
                exitSimulationChoice end_day_choice = getEndDayChoice();
                if (end_day_choice == exitSimulationChoice::Yes) {
                    std::cout << "Enter the file path to save the simulation: " << std::endl;
                    std::string user_input;
                    std::cin >> user_input;
                    std::cout << "Saving simulation..." << std::endl;
                    std::ofstream file(user_input);

                    json jsonData;
                    jsonData["Time"]["hour"] = simulation.getTime().getHour();
                    jsonData["Time"]["min"] = simulation.getTime().getMinute();

                    json recipes;
                    for (Recipe& recipe : simulation.getRecipes()) {
                        json recipe_json;
                        recipe_json["Name"] = recipe.getName();
                        recipe_json["Time"] = recipe.getTime();
                        recipe_json["Difficulty"] = difficulty_to_string(recipe.getDifficulty());

                        json ingredients;
                        for (Ingredient& ingredient : recipe.getIngredients()) {
                            json ingredient_json;
                            ingredient_json["Name"] = ingredient.getName();
                            ingredient_json["Type"] = type_to_string(ingredient.getType());
                            ingredient_json["Calories"] = ingredient.getCalories();
                            ingredients.push_back(ingredient_json);
                        }
                        recipe_json["Ingredients"] = ingredients;

                        json devices;
                        for (Device& device : recipe.getDevices()) {
                            json device_json;
                            device_json["Name"] = device.getName();
                            devices.push_back(device_json);
                        }
                        recipe_json["Devices"] = devices;
                        recipes.push_back(recipe_json);
                    }
                    jsonData["Recipes"] = recipes;

                    json kitchen_ingredients;
                    for (Ingredient& ingredient : simulation.getIngredients()) {
                        json ingredient_json;
                        ingredient_json["Name"] = ingredient.getName();
                        ingredient_json["Type"] = type_to_string(ingredient.getType());
                        ingredient_json["Calories"] = ingredient.getCalories();
                        kitchen_ingredients.push_back(ingredient_json);
                    }
                    jsonData["Kitchen ingredients"] = kitchen_ingredients;

                    json kitchen_devices;
                    for (Device& device : simulation.getDevices()) {
                        json device_json;
                        device_json["Name"] = device.getName();
                        device_json["State"] = state_to_string(device.getState());
                        kitchen_devices.push_back(device_json);
                    }
                    jsonData["Kitchen devices"] = kitchen_devices;
                    file << jsonData << std::endl;
                    file.close();
                    break;
                } else if (end_day_choice == exitSimulationChoice::No) {
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
            simulationInterface(simulation);
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

                json recipes = jsonData["Recipes"];
                std::vector<Recipe> recipe_list;

                for (const auto& recipe : recipes) {
                    std::string name = recipe["Name"];
                    uint recipe_time = recipe["Time"];
                    Difficulty difficulty = to_difficulty(recipe["Difficulty"]);

                    json ingredients = recipe["Ingredients"];
                    std::vector<Ingredient> recipe_ingredients;
                    for (const auto& ingredient : ingredients) {
                        std::string ingredientName = ingredient["Name"];
                        IngredientType ingredientType = to_ingredient_type(ingredient["Type"]);
                        uint calories = ingredient["Calories"];
                        recipe_ingredients.push_back(Ingredient(ingredientName, ingredientType, calories));
                    }

                    json devices = recipe["Devices"];
                    std::vector<Device> recipe_devices;
                    for (const auto& device : devices) {
                        std::string deviceName = device["Name"];
                        recipe_devices.push_back(Device(deviceName, State::clean));
                    }
                    recipe_list.push_back(Recipe(name, recipe_time, difficulty, recipe_ingredients, recipe_devices));
                }

                json ingredients = jsonData["Kitchen ingredients"];
                std::vector<Ingredient> ingredient_list;
                for (const auto& ingredient : ingredients) {
                    std::string name = ingredient["Name"];
                    IngredientType type = to_ingredient_type(ingredient["Type"]);
                    uint calories = ingredient["Calories"];
                    ingredient_list.push_back(Ingredient(name, type, calories));
                }

                json devices = jsonData["Kitchen devices"];
                std::vector<Device> device_list;
                for (const auto& device : devices) {
                    std::string name = device["Name"];
                    State state = to_state(device["State"]);
                    device_list.push_back(Device(name, state));
                }
                file.close();
                Kitchen kitchen = Kitchen(time, recipe_list, ingredient_list, device_list);
                std::cout << "Simulation loaded successfully!" << std::endl;
                simulationInterface(kitchen);
            } else {
                std::cout << "Failed to open the file." << std::endl;
            }
        } else {
            std::cout << "Invalid choice!" << std::endl;
            continue;
        }
    }
    return 0;
}
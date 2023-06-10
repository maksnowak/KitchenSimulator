#include <iostream>
#include <vector>
#include <algorithm>
#include "recipe.h"
#include "device.h"
#include "ingredient.h"
#include "no_ingredients_exception.h"

Recipe::Recipe(std::string name, unsigned short time, Difficulty difficulty, std::vector<Ingredient> ingredients, std::vector<Device> devices) : name(name), time(time), difficulty(difficulty), devices(devices) {
    setIngredients(ingredients);
}

std::string Recipe::getName() {
    return name;
}

unsigned short Recipe::getTime() {
    return time;
}

Difficulty Recipe::getDifficulty() {
    return difficulty;
}

std::vector<Ingredient> Recipe::getIngredients() {
    return ingredients;
}

std::vector<Device> Recipe::getDevices() {
    return devices;
}

void Recipe::setName(std::string new_name) {
    name = new_name;
}

void Recipe::setTime(unsigned short new_time) {
    time = new_time;
}

void Recipe::setDifficulty(Difficulty new_difficulty) {
    difficulty = new_difficulty;
}

void Recipe::setIngredients(std::vector<Ingredient> new_ingredients) {
    if (new_ingredients.size() == 0) {
        throw NoIngredientsException();
    }
    ingredients = new_ingredients;
}

void Recipe::setDevices(std::vector<Device> new_devices) {
    devices = new_devices;
}

unsigned short Recipe::caloricValue() {
    unsigned short value = 0;
    for (Ingredient ingredient : ingredients) {
        value += ingredient.getCalories();
    }
    return value;
}

void Recipe::addIngredient(Ingredient ingredient) {
    ingredients.push_back(ingredient);
}

void Recipe::sortIngredients() {
    std::ranges::sort(ingredients, std::ranges::greater());
}
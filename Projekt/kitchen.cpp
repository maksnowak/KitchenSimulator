#include "kitchen.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "time.h"
#include "recipe.h"
#include "ingredient.h"
#include "device.h"
#include "missing_ingredients_exception.h"
#include "missing_devices_exception.h"

Kitchen::Kitchen(Time time, std::vector<Recipe> recipes, std::vector<Ingredient> ingredients, std::vector<Device> devices) : time(time), recipes(recipes), ingredients(ingredients), devices(devices) {}

Time Kitchen::getTime() {
    return time;
}

std::vector<Recipe> Kitchen::getRecipes() {
    return recipes;
}

std::vector<Ingredient> Kitchen::getIngredients() {
    return ingredients;
}

std::vector<Device> Kitchen::getDevices() {
    return devices;
}

void Kitchen::setTime(Time new_time) {
    time = new_time;
}

void Kitchen::setRecipes(std::vector<Recipe> new_recipes) {
    recipes = new_recipes;
}

void Kitchen::setIngredients(std::vector<Ingredient> new_ingredients) {
    ingredients = new_ingredients;
}

void Kitchen::setDevices(std::vector<Device> new_devices) {
    devices = new_devices;
}

void Kitchen::addRecipe(Recipe new_recipe) {
    recipes.push_back(new_recipe);
}

void Kitchen::buyDevice(Device new_device) {
    devices.push_back(new_device);
}

void Kitchen::buyIngredient(Ingredient new_ingredient) {
    ingredients.push_back(new_ingredient);
}

void Kitchen::cook(Recipe recipe) {
    std::vector<Ingredient> recipe_ingredients = recipe.getIngredients();
    std::vector<Device> recipe_devices = recipe.getDevices();
    std::vector<Ingredient> kitchen_ingredients = getIngredients();
    std::vector<Device> kitchen_devices = getDevices();
    std::vector<Ingredient> missing_ingredients;
    std::vector<Device> missing_devices;
    for (Ingredient recipe_ingredient : recipe_ingredients) {
        if (std::find(kitchen_ingredients.begin(), kitchen_ingredients.end(), recipe_ingredient) == kitchen_ingredients.end()) {
            missing_ingredients.push_back(recipe_ingredient);
        }
    }
    for (Device recipe_device : recipe_devices) {
        if (std::find(kitchen_devices.begin(), kitchen_devices.end(), recipe_device) == kitchen_devices.end()) {
            missing_devices.push_back(recipe_device);
        }
    }
    if (missing_ingredients.size() > 0) {
        throw MissingIngredientsException();
    }
    if (missing_devices.size() > 0) {
        throw MissingDevicesException();
    }
    for (Ingredient recipe_ingredient : recipe_ingredients) {
    }
}
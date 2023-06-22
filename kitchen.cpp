#include "kitchen.h"
#include <vector>
#include <algorithm>
#include "time_unit.h"
#include "recipe.h"
#include "ingredient.h"
#include "device.h"
#include "missing_ingredients_exception.h"
#include "missing_devices_exception.h"
#include "dirty_device_exception.h"

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
    std::vector<Ingredient> missing_ingredients;
    std::vector<Device> missing_devices;
    for (Ingredient& recipe_ingredient : recipe.getIngredients()) {
        if (std::find(ingredients.begin(), ingredients.end(), recipe_ingredient) == ingredients.end()) {
            missing_ingredients.push_back(recipe_ingredient);
        }
    }
    for (Device& recipe_device : recipe.getDevices()) {
        Device kitchen_device = *std::find(devices.begin(), devices.end(), recipe_device);
        if (kitchen_device.getState() == State::dirty) {
            throw DirtyDeviceException();
        }
        if (std::find(devices.begin(), devices.end(), recipe_device) == devices.end()) {
            missing_devices.push_back(recipe_device);
        }
    }
    if (missing_ingredients.size() > 0) {
        throw MissingIngredientsException();
    }
    if (missing_devices.size() > 0) {
        throw MissingDevicesException();
    }
    for (Ingredient& recipe_ingredient : recipe.getIngredients()) {
        std::vector<Ingredient>::iterator ingredient_position = std::find(ingredients.begin(), ingredients.end(), recipe_ingredient);
        ingredients.erase(ingredient_position);
    }
    for (Device& kitchen_device : devices) {
        for (Device& device : recipe.getDevices()) {
            if (kitchen_device == device) {
                kitchen_device.setState(State::dirty);
            }
        }
    }
    time.skip_by(recipe.getTime());
}

void Kitchen::cleanDevices() {
    for (Device& kitchen_device : devices) {
        kitchen_device.setState(State::clean);
    }
}

void Kitchen::takeBreak(uint minutes) {
    time.skip_by(minutes);
}
#pragma once
#include <iostream>
#include <vector>
#include "time.h"
#include "recipe.h"
#include "ingredient.h"
#include "device.h"

class Kitchen {
private:
    Time time;
    std::vector<Recipe> recipes;
    std::vector<Ingredient> ingredients;
    std::vector<Device> devices;
public:
    Kitchen(Time time, std::vector<Recipe> recipes, std::vector<Ingredient> ingredients, std::vector<Device> devices);
    Time getTime();
    std::vector<Recipe> getRecipes();
    std::vector<Ingredient> getIngredients();
    std::vector<Device> getDevices();
    void setTime(Time new_time);
    void setRecipes(std::vector<Recipe> new_recipes);
    void setIngredients(std::vector<Ingredient> new_ingredients);
    void setDevices(std::vector<Device> new_devices);
    void addRecipe(Recipe new_recipe);
    void buyDevice(Device new_device);
    void buyIngredient(Ingredient new_ingredient);
    void cook(Recipe recipe);
    void cleanDevices();
};
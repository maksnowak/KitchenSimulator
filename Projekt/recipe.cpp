#include <iostream>
#include <vector>
#include <algorithm>
#include "recipe.h"
#include "ingredient.h"

Recipe::Recipe(std::string name, unsigned short time, Difficulty difficulty, std::vector<Ingredient> ingredients) : name(name), time(time), difficulty(difficulty), ingredients(ingredients){}

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
    ingredients = new_ingredients;
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
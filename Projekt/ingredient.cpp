#include "ingredient.h"

Ingredient::Ingredient(std::string name, IngredientType type, unsigned short calories) : name(name), type(type), calories(calories) {}

std::string Ingredient::getName() {
    return name;
}

IngredientType Ingredient::getType() {
    return type;
}

unsigned short Ingredient::getCalories() {
    return calories;
}

void Ingredient::setName(std::string new_name) {
    name = new_name;
}

void Ingredient::setType(IngredientType new_type) {
    type = new_type;
}

void Ingredient::setCalories(unsigned short new_calories) {
    calories = new_calories;
}

bool Ingredient::operator<(const Ingredient& other_ingredient) const {
    return calories < other_ingredient.calories;
}

bool Ingredient::operator<=(const Ingredient& other_ingredient) const {
    return calories <= other_ingredient.calories;
}

bool Ingredient::operator>(const Ingredient& other_ingredient) const {
    return calories > other_ingredient.calories;
}

bool Ingredient::operator>=(const Ingredient& other_ingredient) const {
    return calories >= other_ingredient.calories;
}

bool Ingredient::operator==(const Ingredient& other_ingredient) const {
    return calories == other_ingredient.calories;
}

bool Ingredient::operator!=(const Ingredient& other_ingredient) const {
    return calories != other_ingredient.calories;
}

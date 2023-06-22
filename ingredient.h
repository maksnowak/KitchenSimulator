#pragma once
#include <iostream>

enum class IngredientType {
    meat,
    vegetable,
    fruit,
    grain,
    dairy,
    seasoning,
    other
};

class Ingredient {
private:
    std::string name;
    IngredientType type;
    unsigned short int calories;
public:
    Ingredient(std::string name, IngredientType type, unsigned short calories);
    std::string getName();
    IngredientType getType();
    unsigned short getCalories();
    void setName(std::string name);
    void setType(IngredientType type);
    void setCalories(unsigned short calories);
    bool operator<(const Ingredient& other_ingredient) const;
    bool operator<=(const Ingredient& other_ingredient) const;
    bool operator>(const Ingredient& other_ingredient) const;
    bool operator>=(const Ingredient& other_ingredient) const;
    bool operator==(const Ingredient& other_ingredient) const;
    bool operator!=(const Ingredient& other_ingredient) const;
};

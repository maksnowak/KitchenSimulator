#pragma once
#include "ingredient.h"
#include <iostream>
#include <vector>

enum class Difficulty {
    easy,
    medium,
    hard
};

class Recipe {
    private:
        std::string name;
        unsigned short time;
        Difficulty difficulty;
        std::vector<Ingredient> ingredients;
    public:
        Recipe(std::string name, unsigned short time, Difficulty difficulty, std::vector<Ingredient> ingredients);
        std::string getName();
        unsigned short getTime();
        Difficulty getDifficulty();
        std::vector<Ingredient> getIngredients();
        void setName(std::string new_name);
        void setTime(unsigned short new_time);
        void setDifficulty(Difficulty new_difficulty);
        void setIngredients(std::vector<Ingredient> new_ingredients);
        unsigned short caloricValue();
        void addIngredient(Ingredient ingredient);
        void sortIngredients();
};

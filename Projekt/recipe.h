#pragma once
#include "ingredient.h"
#include "device.h"
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
        std::vector<Device> devices;
    public:
        Recipe(std::string name, unsigned short time, Difficulty difficulty, std::vector<Ingredient> ingredients, std::vector<Device> devices);
        std::string getName();
        unsigned short getTime();
        Difficulty getDifficulty();
        std::vector<Ingredient> getIngredients();
        std::vector<Device> getDevices();
        void setName(std::string new_name);
        void setTime(unsigned short new_time);
        void setDifficulty(Difficulty new_difficulty);
        void setIngredients(std::vector<Ingredient> new_ingredients);
        void setDevices(std::vector<Device> new_devices);
        unsigned short caloricValue();
        void addIngredient(Ingredient ingredient);
        void sortIngredients();
};

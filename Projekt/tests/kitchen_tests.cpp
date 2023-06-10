#include "catch_amalgamated.hpp"
#include "../kitchen.h"
#include "../time.h"

// Example kitchen



TEST_CASE("Kitchen tests", "[kitchen]") {
    Time time1(8, 0);
    Ingredient ingredient1("First ingredient", IngredientType::meat, 100);
    Ingredient ingredient2("Second ingredient", IngredientType::vegetable, 200);
    Ingredient ingredient3("Third ingredient", IngredientType::dairy, 300);
    Ingredient ingredient4("Fourth ingredient", IngredientType::grain, 130);
    Device device1("Blender", State::clean);
    Device device2("Pot", State::dirty);
    Device device3("Knife", State::clean);
    Recipe recipe1("Test recipe", 20, Difficulty::easy, {ingredient1, ingredient2}, {device1, device2});
    Recipe recipe2("Test recipe 2", 30, Difficulty::medium, {ingredient3, ingredient4}, {device3});
    Kitchen kitchen(time1, {recipe1}, {ingredient1, ingredient2}, {device1, device2});
    SECTION("Getters") {
        CHECK(kitchen.getTime() == time1);
        CHECK(kitchen.getRecipes() == std::vector<Recipe>({recipe1}));
        CHECK(kitchen.getIngredients() == std::vector<Ingredient>({ingredient1, ingredient2}));
        CHECK(kitchen.getDevices() == std::vector<Device>({device1, device2}));
    }

    SECTION("Setters") {
        Time new_time(9, 0);
        kitchen.setTime(new_time);
        CHECK(kitchen.getTime() == new_time);
        kitchen.setRecipes({recipe2});
        CHECK(kitchen.getRecipes() == std::vector<Recipe>({recipe2}));
        kitchen.setIngredients({ingredient3, ingredient4});
        CHECK(kitchen.getIngredients() == std::vector<Ingredient>({ingredient3, ingredient4}));
        kitchen.setDevices({device3});
        CHECK(kitchen.getDevices() == std::vector<Device>({device3}));
    }

    SECTION("Add recipe") {
        kitchen.addRecipe(recipe2);
        CHECK(kitchen.getRecipes() == std::vector<Recipe>({recipe1, recipe2}));
    }

    SECTION("Buy device") {
        kitchen.buyDevice(device3);
        CHECK(kitchen.getDevices() == std::vector<Device>({device1, device2, device3}));
    }

    SECTION("Buy ingredient") {
        kitchen.buyIngredient(ingredient3);
        CHECK(kitchen.getIngredients() == std::vector<Ingredient>({ingredient1, ingredient2, ingredient3}));
    }

    SECTION("Cook") {
        kitchen.cook(recipe1);
        CHECK(kitchen.getTime() == Time(8, 20));
        CHECK(kitchen.getDevices() == std::vector<Device>({device1, device2}));
        CHECK(kitchen.getIngredients() == std::vector<Ingredient>({}));
        kitchen.buyIngredient(ingredient3);
        kitchen.buyIngredient(ingredient4);
        kitchen.buyDevice(device3);
        kitchen.cook(recipe2);
        CHECK(kitchen.getTime() == Time(8, 50));
        CHECK(kitchen.getDevices() == std::vector<Device>({device1, device2, device3}));
        CHECK(kitchen.getIngredients() == std::vector<Ingredient>({}));
    }
}
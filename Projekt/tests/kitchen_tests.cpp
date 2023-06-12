#include "catch_amalgamated.hpp"
#include "../kitchen.h"
#include "../time.h"
#include "../missing_ingredients_exception.h"
#include "../missing_devices_exception.h"
#include "../dirty_device_exception.h"

TEST_CASE("Kitchen tests", "[kitchen]") {
    Time time(8, 0);
    Ingredient ingredient1("First ingredient", IngredientType::meat, 100);
    Ingredient ingredient2("Second ingredient", IngredientType::vegetable, 200);
    Ingredient ingredient3("Third ingredient", IngredientType::dairy, 300);
    Ingredient ingredient4("Fourth ingredient", IngredientType::grain, 130);
    Device device1("Blender", State::clean);
    Device device2("Pot", State::dirty);
    Device device3("Knife", State::clean);
    Device device4("Fork", State::dirty);
    Device device5("Oven", State::clean);
    Recipe recipe1("Test recipe", 20, Difficulty::easy, {ingredient1, ingredient2}, {device1, device2});
    Recipe recipe2("Test recipe 2", 30, Difficulty::medium, {ingredient3, ingredient4}, {device3});
    Recipe recipe3("Test recipe 3", 40, Difficulty::hard, {ingredient1, ingredient2}, {device5});
    Kitchen kitchen(time, {recipe1}, {ingredient1, ingredient2}, {device1, device2});
    SECTION("Getters") {
        CHECK(kitchen.getTime() == time);
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

    SECTION("Cleaning") {
        kitchen.cleanDevices();
        CHECK(kitchen.getDevices().size() == 2);
        for (auto& device : kitchen.getDevices()) {
            CHECK(device.getState() == State::clean);
        }
    }

    SECTION("Cook") {
        CHECK_THROWS_AS(kitchen.cook(recipe1), DirtyDeviceException);
        kitchen.cleanDevices();
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

    SECTION("Exceptions") {
        CHECK_THROWS_AS(kitchen.cook(recipe3), MissingDevicesException);
        kitchen.cleanDevices();
        kitchen.cook(recipe1);
        CHECK_THROWS_AS(kitchen.cook(recipe1), DirtyDeviceException);
        kitchen.cleanDevices();
        CHECK_THROWS_AS(kitchen.cook(recipe1), MissingIngredientsException);
    }
}

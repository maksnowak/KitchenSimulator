#include "catch_amalgamated.hpp"
#include "../recipe.h"
#include "../no_ingredients_exception.h"

// Example ingredients
Ingredient ingredient1("First ingredient", IngredientType::meat, 100);
Ingredient ingredient2("Second ingredient", IngredientType::vegetable, 200);
Ingredient ingredient3("Third ingredient", IngredientType::dairy, 300);
Ingredient ingredient4("Fourth ingredient", IngredientType::grain, 130);

Device device1("Blender", State::clean);
Device device2("Pot", State::dirty);
Device device3("Knife", State::clean);

TEST_CASE("Recipe tests", "[recipe]") {
    Recipe recipe("Test recipe", 20, Difficulty::easy, {ingredient1, ingredient2}, {device1, device2});
    CHECK(recipe.getName() == "Test recipe");
    CHECK(recipe.getTime() == 20);
    CHECK(recipe.getDifficulty() == Difficulty::easy);

    SECTION("Checking if ingridient vector is correct"){
        CHECK(recipe.getIngredients()[0].getType() == IngredientType::meat);
        CHECK(recipe.getIngredients()[0].getCalories() == 100);
        CHECK(recipe.getIngredients()[1].getType() == IngredientType::vegetable);
        CHECK(recipe.getIngredients()[1].getCalories() == 200);
        CHECK(recipe.getIngredients().size() == 2);
    }

    SECTION("Checking if device vector is correct"){
        CHECK(recipe.getDevices()[0].getName() == "Blender");
        CHECK(recipe.getDevices()[0].getType() == State::clean);
        CHECK(recipe.getDevices()[1].getName() == "Pot");
        CHECK(recipe.getDevices()[1].getType() == State::dirty);
        CHECK(recipe.getDevices().size() == 2);
    }

    SECTION("Setting new values") {
        recipe.setName("New name");
        recipe.setTime(130);
        recipe.setDifficulty(Difficulty::easy);
        recipe.setIngredients({ingredient4});
        CHECK(recipe.getName() == "New name");
        CHECK(recipe.getTime() == 130);
        CHECK(recipe.getDifficulty() == Difficulty::easy);
        CHECK(recipe.getIngredients()[0].getType() == IngredientType::grain);
        CHECK(recipe.getIngredients()[0].getCalories() == 130);
        CHECK(recipe.getIngredients().size() == 1);
    }

    SECTION("Setting recipe ingredients as an empty vector") {
        CHECK_THROWS_AS(recipe.setIngredients({}), NoIngredientsException);
    }

    SECTION("Setting recipe devices as an empty vector") {
        recipe.setDevices({});
        CHECK(recipe.getDevices().size() == 0);
    }

    SECTION("Adding ingredients to existing ones") {
        recipe.addIngredient(ingredient3);
        recipe.addIngredient(ingredient4);
        CHECK(recipe.getIngredients()[0].getType() == IngredientType::meat);
        CHECK(recipe.getIngredients()[0].getCalories() == 100);
        CHECK(recipe.getIngredients()[1].getType() == IngredientType::vegetable);
        CHECK(recipe.getIngredients()[1].getCalories() == 200);
        CHECK(recipe.getIngredients()[2].getType() == IngredientType::dairy);
        CHECK(recipe.getIngredients()[2].getCalories() == 300);
        CHECK(recipe.getIngredients()[3].getType() == IngredientType::grain);
        CHECK(recipe.getIngredients()[3].getCalories() == 130);
        CHECK(recipe.getIngredients().size() == 4);
    }

    SECTION("Counting caloric value of recipe") {
        CHECK(recipe.caloricValue() == 300);
    }

    SECTION("Counting caloric value of recipe with added ingredients") {
        recipe.addIngredient(ingredient3);
        CHECK(recipe.caloricValue() == 600);
    }

    SECTION("Sorting ingredients by caloric value (descending)") {
        recipe.addIngredient(ingredient3);
        recipe.addIngredient(ingredient4);
        recipe.sortIngredients();
        CHECK(recipe.getIngredients()[0].getType() == IngredientType::dairy);
        CHECK(recipe.getIngredients()[0].getCalories() == 300);
        CHECK(recipe.getIngredients()[1].getType() == IngredientType::vegetable);
        CHECK(recipe.getIngredients()[1].getCalories() == 200);
        CHECK(recipe.getIngredients()[2].getType() == IngredientType::grain);
        CHECK(recipe.getIngredients()[2].getCalories() == 130);
        CHECK(recipe.getIngredients()[3].getType() == IngredientType::meat);
        CHECK(recipe.getIngredients()[3].getCalories() == 100);
        CHECK(recipe.getIngredients().size() == 4);
    }
}
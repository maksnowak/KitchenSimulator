#include "catch_amalgamated.hpp"
#include "../ingredient.h"

TEST_CASE("Ingredient tests", "[ingredient]") {
    Ingredient ingredient("Test ingredient", IngredientType::meat, 100);
    CHECK(ingredient.getName() == "Test ingredient");
    CHECK(ingredient.getType() == IngredientType::meat);
    CHECK(ingredient.getCalories() == 100);

    SECTION("Setting new values") {
        ingredient.setName("Another ingredient");
        ingredient.setType(IngredientType::dairy);
        ingredient.setCalories(300);
        CHECK(ingredient.getName() == "Another ingredient");
        CHECK(ingredient.getType() == IngredientType::dairy);
        CHECK(ingredient.getCalories() == 300);
    }

    SECTION("Comparing two different ingredients") {
        Ingredient other_ingredient("Other ingredient", IngredientType::vegetable, 200);
        CHECK(ingredient < other_ingredient);
        CHECK(ingredient <= other_ingredient);
        CHECK(other_ingredient > ingredient);
        CHECK(other_ingredient >= ingredient);
        CHECK(ingredient != other_ingredient);
        CHECK_FALSE(ingredient == other_ingredient);
    }

    SECTION("Comparing two ingredients with the same caloric value") {
        Ingredient other_ingredient("Other ingredient", IngredientType::vegetable, 100);
        CHECK_FALSE(ingredient < other_ingredient);
        CHECK(ingredient <= other_ingredient);
        CHECK_FALSE(other_ingredient > ingredient);
        CHECK(other_ingredient >= ingredient);
        CHECK(ingredient == other_ingredient);
        CHECK_FALSE(ingredient != other_ingredient);
    }

    SECTION("Comparing the ingredient with itself") {
        CHECK_FALSE(ingredient < ingredient);
        CHECK(ingredient <= ingredient);
        CHECK_FALSE(ingredient > ingredient);
        CHECK(ingredient >= ingredient);
        CHECK(ingredient == ingredient);
        CHECK_FALSE(ingredient != ingredient);
    }
}
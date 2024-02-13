# KitchenSimulator

This repository contains a simple kitchen simulator written in C++.

The kitchen contains recipes, kitchen devices and products necessary to make food.

## Program assumptions

- Simulator can do one of the things listed below:
    - Buying (creating) ingredients
    - Buying (creating) kitchen devices
    - Washing the devices
    - Cooking
    - Creating a new recipe
    - Listing all recipes
    - Listing all ingredients
    - Listing all devices
- Everything takes a specified amount of time
- After finishing cooking the device cannot be used until it is cleaned
- Every ingredient can be used once
- The recipe has to have ingredients but does not require devices

## Run the program

In order to launch the program correctly, you have to:

1. Clone the repository - `git clone https://github.com/maksnowak/KitchenSimulator.git`
2. Download [the spdlog include directory](https://github.com/gabime/spdlog/tree/v1.x/include/spdlog) and [nlohmann's json header file](https://github.com/nlohmann/json/blob/develop/single_include/nlohmann/json.hpp) 
3. Place all the files in the root directory of the repository
4. Compile the program - `g++ -std=c++20 path/to/repository/*.cpp -o path/to/repository/KitchenSimulator -I /path/to/program -Wall -Werror`
5. Run the program - `./KitchenSimulator`

### Launching unit tests

To launch unit tests, download the `catch_amalgamated` files from [here](https://github.com/catchorg/Catch2/tree/devel/extras), place them in the `tests` directory and then compile both the program and test files.

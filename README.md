# KitchenSimulator

This repository contains a C++ project written for Object-Oriented Programming class at Warsaw University of Technology.

It is a simple kitchen simulation - you can buy ingredients, devices, make recipes, etc.

In order to launch the program correctly, you have to:

1. Download [the spdlog include directory](https://github.com/gabime/spdlog/tree/v1.x/include/spdlog) and [nlohmann's json header file](https://github.com/nlohmann/json/blob/develop/single_include/nlohmann/json.hpp) 
2. Place all the files in the root directory of the repository
3. To launch unit tests, download the `catch_amalgamated` files from [here](https://github.com/catchorg/Catch2/tree/devel/extras) and place them in the `tests` directory

You can find fragments of the original documentation below (in Polish)

---

# PROI - dokumentacja wstępna projektu

## Cel i założenie projektu

Tematem projektu jest stworzenie programu, który będzie symulował kuchnię. Na kuchnię będą się składać przepisy, przyrządy kuchenne oraz produkty potrzebne do ich wykonania.

Kuchnia działa przy następujących założeniach:
- Symulator umożliwia wykonanie jednej z następujących czynności:
    - Zakup (utworzenie) składników
    - Zakup (utworzenie) przyrządu kuchennego
    - Umycie przyrządów kuchennych
    - Rozpoczęcie gotowania
    - Stworzenie nowego przepisu
    - Wyświetlenie wszystkich przepisów
    - Wyświetlenie wszystkich składników
    - Wyświetlenie wszystkich przyrządów
- Każda z czynności zajmuje określoną ilość czasu.
- Po zakończeniu gotowania przyrządu nie będzie można użyć, dopóki nie zostanie on umyty
- Składniki mogą zostać użyte tylko raz
- Przepis musi zawierać składniki ale nie musi zawierać przyrządów

## Uruchomienie programu

1. Skolonowanie repozytorium za pomocą komendy: `git clone https://github.com/maksnowak/KitchenSimulator.git` lub jego pobranie
2. Kompilacja programu: `g++ -std=c++20 <ścieżka do repozytorium>/*.cpp -o <ścieżka do repozytorium>/KitchenSimulator -I <ścieżka do programu> -Wall -Werror`
3. Uruchomienie programu (zakładając że znajdujemy się w katalogu repozytorium): `./KitchenSimulator`

## Podział programu

Program jest podzielony na klasy, reprezentujące poszczególne elementy symulatora. W klasach będą znajdować się operacje z nimi związane.
Oprócz tego, w głównym pliku programu jest zawarty interfejs użytkownika.

Najważniejsze klasy, które znajdują się w programie:
- Klasa kuchni - jest podstawą działania symulacji, zawiera zmnienne przechowujące aktualny czas, przepisy, składniki i przyrządy oraz funkcje odpowiadające za czynności możliwe do wykonania przez symulator
- Klasa przepisu - zawiera nazwę, czas wykonania i potrzebne składniki oraz przyrządy kuchenne
- Klasa składnika - zawiera nazwę, typ (mięso, nabiał, itp.) oraz wartość kaloryczną
- Klasa przyrządu - zawiera nazwę, stan czystości oraz metody jej działania
- Klasa jednostki czasu - zawiera godzinę w formacie `godzina:minuta` oraz metody pozwalające na pominięcie okresu czasu określonego przez użytkownika

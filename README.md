# PROI - dokumentacja wstępna projektu

*Adam Czupryński, Maksymilian Nowak*

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

1. Skolonowanie repozytorium za pomocą komendy: `git clone https://gitlab-stud.elka.pw.edu.pl/mnowak1/Maksymilian_Nowak_PROI23L.git` lub jego pobranie
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

## Relacje między poszczególnymi klasami

![](https://drive.google.com/uc?export=view&id=1-8rTOxuO9gBIH18Se3j1Irwk7a7C7bfw)

## Dodatkowe funkcje projektu
Projekt umożliwia zapisywanie aktualnego stanu kuchni do pliku JSON a przy uruchamianiu symulacji istnieje możliwość wczytania istniejącej już symulacji. Wszystkie klasy projektu przeszły testy jednostkowe sprawdzające ich poprawne działanie w skrajnych przypadkach.
[](https://drive.google.com/uc?id=1sxgWBhjks9O90A9eLVgH1G7n1S8lzgmh)
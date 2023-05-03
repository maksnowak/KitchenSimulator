# PROI - dokumentacja wstępna projektu

*Adam Czupryński, Maksymilian Nowak*

## Cel i założenie projektu

Tematem projektu jest stworzenie programu, który będzie symulował kuchnię. Na kuchnię będą się składać przepisy, przyrządy kuchenne oraz produkty potrzebne do ich wykonania.

Kuchnia będzie działać przy następujących założeniach:
- Symulator będzie umożliwiał wykonanie jednej z następujących czynności:
    - Zakup (utworzenie) składników
    - Umycie przyrządów kuchennych
    - Rozpoczęcie gotowania
    - Stworzenie nowego przepisu
- Każda z czynności zajmuje określoną ilość czasu.
- Po zakończeniu gotowania przyrządu nie będzie można użyć, dopóki nie zostanie on umyty
- Składniki mogą zostać użyte tylko raz

## Podział programu

Program będzie podzielony na klasy, reprezentujące poszczególne elementy symulatora. W klasach będą znajdować się operacje z nimi związane.
Oprócz tego, w głównym pliku programu będzie zawarty interfejs użytkownika.

Najważniejsze klasy, które znajdą się w programie:
- Klasa przepisu - będzie zawierać nazwę, czas wykonania i potrzebne składniki oraz przyrządy kuchenne
- Klasa składnika - będzie zawierać nazwę, typ (mięso, nabiał, itp.) oraz wartość kaloryczną
- Klasa przyrządu - będzie zawierać nazwę oraz stan czystości

## Relacje między poszczególnymi klasami

![](https://drive.google.com/uc?id=1sxgWBhjks9O90A9eLVgH1G7n1S8lzgmh)
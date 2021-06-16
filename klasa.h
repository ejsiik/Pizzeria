#pragma once
#include <iostream>
#include <string>
using namespace std;

class Pizzeria;
void pause();
void blad();
void login();
void powitanie();
void plik(int nr2, string pizza, double cena, bool czyNaWynos, string adres = "");
Pizzeria* DodajZamowienie(Pizzeria*& head, string pizza, double cena, bool czyNaWynos, string adres, int& nr2);
Pizzeria* ZnajdzZamowienie(Pizzeria* head, int nr_zam);
Pizzeria* ZnajdzZamowienie2(Pizzeria* head, string pizza);
Pizzeria* czyIstnieje(Pizzeria* head, int  nr_zam);
void usun(Pizzeria*& head, int& nr_zam);
void wypisz(Pizzeria* head);
void wyczysc(Pizzeria*& head);

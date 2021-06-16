#include "klasa.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <conio.h> //_getch()
#include <fstream> //pliki
using namespace std;

class Pizzeria {
public:
	string pizza;
	double cena;
	bool czyNaWynos;
	string adres;
	int nr_zam;
	Pizzeria* nastepny;
	Pizzeria* poprzedni;
};

Pizzeria* DodajZamowienie(Pizzeria*& head, string pizza, double cena, bool czyNaWynos, string adres, int& nr2) {
	nr2++;
	plik(nr2, pizza, cena, czyNaWynos, adres);
	if (head == nullptr){ //jesli klasa nie zawiera zadnych danych
		head = new Pizzeria{ pizza, cena, czyNaWynos, adres, nr2 };
		cout << "\t\tZamowienie " << pizza << " zostalo dodane do bazy danych " << "\n";
		Sleep(1500);
		return head;
	}

	Pizzeria* temp = head;
	while (temp->nastepny) //"przemieszczanie sie" po elementach klasy
		temp = temp->nastepny;

	temp->nastepny = new Pizzeria{ pizza, cena, czyNaWynos, adres, nr2 };
	temp->nastepny->poprzedni = temp;
	cout << "\t\tZamowienie " << pizza << " zostalo dodane do bazy danych " << "\n";
	Sleep(1500);
	return temp->nastepny;
}

Pizzeria* ZnajdzZamowienie(Pizzeria* head, int nr_zam){
	
	if (head == nullptr){
		cout << "\t\tBrak zamowien\n";
		Sleep(1500);
		return head;
	}

	while (head)
	{
		if (head->nr_zam == nr_zam)
		{
			cout << "\t\tPizza: " << head->pizza << " cena " << head->cena << " gdzie: " << head->czyNaWynos
				<< " adres " << head->adres << "\n";
			pause();
			return head;
		}
		head = head->nastepny;
	}
	cout << "\t\tBrak zamowien o takim id\n";
	Sleep(1500);
	return nullptr;
}

Pizzeria* ZnajdzZamowienie2(Pizzeria* head, string pizza) {
	
	if (head == nullptr) {
		cout << "\t\tBrak zamowien\n";
		Sleep(1500);
		return head;
	}

	while (head)
	{
		if (head->pizza == pizza)
		{
			cout << "\t\tPizza: " << head->pizza << " cena: " << head->cena << " gdzie: " << head->czyNaWynos
				<< " adres " << head->adres << "\n";
			pause();
			return head;
		}
		head = head->nastepny;
	}
	cout << "\t\tBrak zamowien o takim id\n";
	Sleep(1500);
	return nullptr;
}

Pizzeria* czyIstnieje(Pizzeria* head, int nr_zam) {
	while (head)
	{
		if (head->nr_zam == nr_zam)
		{
			return head;
		}
		head = head->nastepny;
	}
	return nullptr;
}



void pause()
{
	cout << "\n\n\n\n\t\tAby kontynuowac wcisnij enter";
	cin.clear();
	cin.ignore(1000, '\n');
}

void blad() {
	cout << "\n\n\n\n\t\t\tBLAD, PODAJ POPRAWNA WARTOSC";
	Sleep(2000);
	system("cls");
}

void login()
{
	system("cls");
	string haslo = "";
	char ch;
	cout << "\n\n\n\n\n\n\n\t\t\t\t\tSYSTEM LOGOWANIA";
	cout << "\n\n\n\n\n\n\t\t\t\t\tWPROWADZ HASLO: ";
	ch = _getch();
	while (ch != 13)  //* aby zamaskowac wprowadzane haslo
	{
		haslo.push_back(ch);
		cout << '*';
		ch = _getch();
	}
	if (haslo == "admin")
	{
		cout << "\n\n\n\n\t\t\tLOGOWANIE POWIODLO SIE | ZAPRASZAM DO KORZYSTANIA Z PROGRAMU \n\n";
		Sleep(2000);
	}
	else
	{
		cout << "\n\n\n\n\t\t\tLOGOWANIE NIE POWIODLO SIE | SPROBUJ PONOWNIE\n\n";
		Sleep(2000);
		login();
	}
}

void powitanie()
{
menu:
	system("cls");
	cout << "\n\n\t\t====== MENU ======\n\n";
	cout << "\t\t" << setw(20) << setfill('=') << "=\n\n";
	cout << "\t\t1. LOGOWANIE\n\n";
	cout << "\t\t2. INSTRUKCJA\n\n";
	cout << "\t\t" << setw(20) << setfill('=') << "=\n\n";
	cout << "\t\tTWOJ WYBOR: ";
	int opcja;
	while (!(cin >> opcja && isspace(cin.peek())) || opcja > 2 || opcja < 1)
	{
		cout << "\n\t\tBLAD, PODAJ POPRAWNA WARTOSC: ";
		cin.clear();
		cin.ignore(1000, '\n');
	}
	cin.clear();
	cin.ignore(1000, '\n');

	switch (opcja)
	{
	case 1:
		login();
		break;
	case 2:
		system("cls");
		cout << "INSTRUKCJE HERE";
		cout << "\n\n\n\nAby kontynuowac wcisnij enter";
		cin.clear();
		cin.ignore(1000, '\n');
		goto menu;
	}
}

void plik(int nr2, string pizza, double cena, bool czyNaWynos, string adres) {
	fstream plik; //dopisanie do konca pliku danych kolejnego zamowienia
	plik.open("pizzeria.txt", ios::out | ios::app);
	if (plik.is_open())
	{
		plik << nr2<< ". Pizza: " << setw(4) << setfill(' ') << pizza << " ||" << setw(8) << setfill(' ')
			<< " cena: " << setw(16) << setfill(' ') << cena << " ||" << setw(8) << setfill(' ') << "gdzie: ";
		if (czyNaWynos == 1) {
			plik << " na miejscu \n";
		}
		else {
			plik << " na wynos " << setw(16) << setfill(' ') << " adres: " << setw(9) << setfill(' ') << adres << "\n";
		}
		plik.close();
	}
	else
		cout << "Nie udalo sie otworzyc pliku.\n";
}

void usun(Pizzeria*& head, int& nr_zam) {
	if (head == nullptr) { //jesli nie ma zamowien
		cout << "\t\tBrak zamowien\n";
	}
	else if (head->poprzedni == nullptr && head->nastepny == nullptr) { //jesli usuwamy ostatnie zamowienie
		Pizzeria* tmp = czyIstnieje(head, nr_zam);
		if (tmp) { //jesli istnieje takie zamowienie
			cout << "\n\t\tZamowienie " << tmp->pizza << " zostalo usuniete\n";
			delete head;
			head = nullptr;
		}
		else
			cout << "\t\tBrak zamowien o takim id\n";
	}
	else
	{
		Pizzeria* tmp = czyIstnieje(head, nr_zam);
		if (tmp) //jesli istnieje
		{
			Pizzeria* poprzedni{ tmp->poprzedni };
			Pizzeria* nastepny{ tmp->nastepny };
			if (tmp->poprzedni == nullptr) //jesli zamowienie jest pierwsze
			{
				head = head->nastepny;
				head->poprzedni = nullptr;
			}
			else if (tmp->nastepny == nullptr) //jesli zamowienie jest ostatnie
			{
				poprzedni->nastepny = nullptr;
			}
			else //jesli zamowienie jest "otoczone" innymi zamowieniami
			{
				poprzedni->nastepny = nastepny;
				nastepny->poprzedni = poprzedni;
			}
			cout << "\n\t\tZamowienie " << tmp->pizza << " zostalo usuniete\n";
			delete tmp;
		}
		else
			cout << "\t\tBrak zamowien o takim id\n";
	}
}

void wypisz(Pizzeria* head) {
	if (head == nullptr)
		cout << "\t\tBrak zamowien\n";
	else{
		int ilosc{};
		cout << "\t\tDzisiejsze zamowienia:\n\n";
		while (head){
			cout << "\t\t" << head->nr_zam << ". Pizza: " << setw(4) << setfill(' ') << head->pizza << " ||" << setw(8) << setfill(' ') << " cena: " << setw(16) << setfill(' ') << head->cena
				<< " ||" << setw(8) << setfill(' ') << " gdzie: ";
			if (head->czyNaWynos == 0) {
				cout << setw(8) << setfill(' ') << "na miejscu \n";
			}
			else {
				cout << setw(8) << setfill(' ') << "na wynos ||" << setw(9) << setfill(' ')
					<< "adres: " << setw(10) << setfill(' ') << head->adres << "\n";
			}
			head = head->nastepny;
			ilosc++;
		}
		cout << "\n\t\tIlosc zamowien: " << ilosc;
	}
	pause();
}

void wyczysc(Pizzeria*& head)
{
	while (head)
	{
		Pizzeria* temp = head;
		head = head->nastepny;
		delete temp;
	}
	head = nullptr;
}

#include "klasa.h"
#include <iostream>
#include <iomanip> //setw
#include <string> //string
#include <Windows.h> //sleep, system
#include <cctype> //isspace
#include <fstream> //pliki
#include <winbase.h> //systemtime
using namespace std;

int main()
{
    system("color f1");
    //powitanie();
    system("cls");

    fstream program; //dodanie aktualnej daty do pliku
    program.open("pizzeria.txt", ios::out | ios::app);
    if (program.is_open()) {
        SYSTEMTIME st;
        GetSystemTime(&st);
        program << "\t\t\tData: " << st.wDay << "." << st.wMonth << "." << st.wYear << '\n';
        program.close();
    }
    else
        cout << "Nie udalo sie otworzyc pliku.\n";

    Pizzeria* head = nullptr; //tworzę obiekt klasy

    string opcja;
    string pizza;
    double cena;
    bool wynos;
    string adres;
    int nr;
    int nr2 = 0;

    bool programotwarty = true;

    while (programotwarty == true)
    {
        cout << "\n\n\t\t====== SYSTEM OBSLUGI PIZZERII ======\n\n";
        cout << "\t\t" << setw(50) << setfill('=') << "=\n\n";
        cout << "\t\t1. DODAJ ZAMOWIENIE\n\n";
        cout << "\t\t2. USUN ZAMOWIENIE\n\n";
        cout << "\t\t3. LISTA ZAMOWIEN\n\n";
        cout << "\t\t4. WYSZUKAJ ZAMOWIENIE\n\n";
        cout << "\t\t5. WYJSCIE Z PROGRAMU\n\n";
        cout << "\t\t" << setw(50) << setfill('=') << "=\n\n";
        cout << "\t\tTWOJ WYBOR: ";
		getline(cin, opcja);
		system("cls");
        if (opcja[0] == '1')
        {
            cout << "pizza: ";
            getline(cin,pizza);
            cout << "cena :";
            cin >> cena;
            cout << "na wynos? (0 - nie, 1 - tak): ";
            cin >> wynos;
            cout << "adres: ";
            cin.ignore();
            getline(cin,adres);
            DodajZamowienie(head, pizza, cena, wynos, adres, nr2);
            system("cls");
        }
        else if (opcja[0] == '2')
        {
            cout << "numer zamowienia: ";
            cin >> nr;
            usun(head, nr);
            Sleep(2000);
            system("cls");
        }
        else if (opcja[0] == '3')
        {
            wypisz(head);
        }
        else if (opcja[0] == '4')
        {
            while (opcja[0] != '1' && opcja[0] != '2')
            {
                cout << "1 - szukaj po numerze, 2 - szukaj po pizzy: ";
                getline(cin, opcja);
            }
            if (opcja[0] == '1')
            {
                cout << "podaj numer: ";
                cin >> nr;
                ZnajdzZamowienie(head, nr);
            }
            else if (opcja[0] == '2')
            {
                cout << "podaj pizze: ";
                getline(cin,pizza);
                ZnajdzZamowienie2(head, pizza);
            }
        }
        else if (opcja[0] == '5')
        {
            programotwarty = false;
            wyczysc(head);
        }
    }
    cout << "##komunikat_wyjscia##" << endl;
    system("pause");
    return 0;
}


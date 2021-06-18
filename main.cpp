#include "klasa.h"

int main() {
    system("color f1");
    powitanie();
    system("cls");

    fstream program; //dodanie aktualnej daty do pliku
    program.open("pizzeria.txt", ios::out | ios::app);
    if (program.is_open()) {
        SYSTEMTIME st;
        GetLocalTime(&st);
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
    double cenaSuma = 0;

    bool programotwarty = true;

    while (programotwarty == true)
    {
        system("cls");
        cout << "\n\n====== SYSTEM OBSLUGI PIZZERII ======\n\n";
        cout << setw(39) << setfill('=') << "=\n\n";
        cout << " 1. DODAJ ZAMOWIENIE\n\n";
        cout << " 2. USUN ZAMOWIENIE\n\n";
        cout << " 3. LISTA ZAMOWIEN\n\n";
        cout << " 4. WYSZUKAJ ZAMOWIENIE\n\n";
        cout << " 5. WYJSCIE Z PROGRAMU\n\n";
        cout << setw(39) << setfill('=') << "=\n\n";
        cout << "TWOJ WYBOR: ";
        getline(cin, opcja);
        system("cls");
        if (opcja.size() > 1) {
            blad();
        }
        else if (opcja[0] == '1') {
            cout << "\n\nPizza: ";
            getline(cin, pizza);
            cout << "Cena: ";
            cin >> cena;
            cin.ignore(1000, '\n');
            while (cin.fail()) { 
                cin.clear();
                cin.ignore(1000, '\n');
                cout << " BLAD, PODAJ POPRAWNA WARTOSC\n";
                cout << "Cena: ";
                cin >> cena;
                cin.ignore(1000, '\n');
            }
            cout << "Na wynos? (0 - nie, 1 - tak): ";
            cin >> wynos;
            cin.ignore(1000, '\n');
            while (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << " BLAD, PODAJ POPRAWNA WARTOSC\n";
                cout << "Na wynos? (0 - nie, 1 - tak): ";
                cin >> wynos;
                cin.ignore(1000, '\n');
            }
            if (wynos == 1) {
                cout << "Adres: ";
                getline(cin, adres);
            }
            DodajZamowienie(head, pizza, cena, wynos, adres, nr2, cenaSuma);
        }
        else if (opcja[0] == '2')
        {
            cout << "\n";
            if (head == nullptr) {
                cout << "Brak zamowien";
                Sleep(1500);
            }
            else {
                cout << "Numer zamowienia: ";
                cin >> nr;
                cin.ignore(1000, '\n');
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << " BLAD, PODAJ POPRAWNA WARTOSC\n";
                    cout << "Podaj numer: ";
                    cin >> nr;
                    cin.ignore(1000, '\n');
                }
                usun(head, nr, cenaSuma);
                Sleep(2000);
            }
        }
        else if (opcja[0] == '3')
        {
            wypisz(head);
        }
        else if (opcja[0] == '4')
        {
            cout << "\n";
            if (head == nullptr) {
                cout << "Brak zamowien";
                Sleep(1500);
            }
            else {
                while (opcja[0] != '1' && opcja[0] != '2')
                {
                    cout << " 1 - Szukaj po numerze  2 - Szukaj po pizzy\n\nTwoj wybor: ";
                    getline(cin, opcja);
                }
                if (opcja.size() > 1) {
                    blad();
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                else if (opcja[0] == '1')
                {
                    cout << "\nPodaj numer: ";
                    cin >> nr;
                    cin.ignore(1000, '\n');
                    while (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << " BLAD, PODAJ POPRAWNA WARTOSC\n";
                        cout << "Podaj numer: ";
                        cin >> nr;
                        cin.ignore(1000, '\n');
                    }
                    cout << "\n\n";
                    ZnajdzZamowienie(head, nr);
                }
                else if (opcja[0] == '2')
                {
                    cout << "\nPodaj pizze: ";
                    getline(cin, pizza);
                    cout << "\n\n";
                    ZnajdzZamowienie2(head, pizza);
                }
                else {
                    blad();
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
            }
        }
        else if (opcja[0] == '5')
        {
            programotwarty = false;
            wyczysc(head);
        }
        else {
            blad();
        }
    }
    cout << "\n\nDziekujemy, milego dnia :)\n\n";
    cout << "Zebrane pieniadze: " << cenaSuma << "zl" << "\n\n\n\n";
    system("pause");
    return 0;
}

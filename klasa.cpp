#include "klasa.h"

class Pizzeria {
public:
	string pizza;
	double cena;
	bool czyNaWynos;
	string adres;
	int nr_zam;
	SYSTEMTIME st;
	Pizzeria* nastepny;
	Pizzeria* poprzedni;
};

Pizzeria* DodajZamowienie(Pizzeria*& head, string pizza, double cena, bool czyNaWynos, string adres, int& nr2, double& cenaSuma) {
	cout << "\n";
	nr2++;
	plik(nr2, pizza, cena, czyNaWynos, adres);
	SYSTEMTIME st;
	GetLocalTime(&st);
	if (head == nullptr) { //jesli klasa nie zawiera zadnych danych
		head = new Pizzeria{ pizza, cena, czyNaWynos, adres, nr2, st};
		cenaSuma = cenaSuma + cena;
		cout << "Zamowienie " << pizza << " zostalo dodane do bazy danych " << "\n";
		Sleep(1500);
		return head;
	}

	Pizzeria* temp = head;
	while (temp->nastepny) //"przemieszczanie sie" po elementach klasy
		temp = temp->nastepny;

	temp->nastepny = new Pizzeria{ pizza, cena, czyNaWynos, adres, nr2, st};
	temp->nastepny->poprzedni = temp;
	cenaSuma = cenaSuma + cena;
	cout << "Zamowienie " << pizza << " zostalo dodane do bazy danych " << "\n";
	Sleep(1500);
	return temp->nastepny;
}

Pizzeria* ZnajdzZamowienie(Pizzeria* head, int nr_zam) {
	cout << "\n";
	if (head == nullptr) {
		cout << "Brak zamowien\n";
		Sleep(1500);
		return head;
	}

	while (head) {
		if (head->nr_zam == nr_zam) {
			cout << setw(2) << setfill('0') << head->st.wHour << ":" << setw(2) << setfill('0') << head->st.wMinute << "\t" << head->nr_zam << ". Pizza: " << setw(15) << setfill(' ') << head->pizza << " ||" << setw(8) << setfill(' ')
				<< " cena: " << setw(6) << setfill(' ') << head->cena << " ||" << setw(8) << setfill(' ') << "gdzie: ";
			if (head->czyNaWynos == 0) {
				cout << " na miejscu\n";
			}
			else {
				cout << " na wynos " << setw(8) << setfill(' ') << " adres: " << head->adres << "\n";
			}
			pause();
			return head;
		}
		head = head->nastepny;
	}
	cout << "Brak zamowien o takim id\n";
	Sleep(1500);
	return nullptr;
}

Pizzeria* ZnajdzZamowienie2(Pizzeria* head, string pizza) {
	cout << "\n";
	if (head == nullptr) {
		cout << "Brak zamowien\n";
		Sleep(1500);
		return head;
	}

	while (head) {
		if (head->pizza == pizza) {
			cout << setw(2) << setfill('0') << head->st.wHour << ":" << setw(2) << setfill('0') << head->st.wMinute << "\t" << head->nr_zam << ". Pizza: " << setw(15) << setfill(' ') << head->pizza << " ||" << setw(8) << setfill(' ')
				<< " cena: " << setw(6) << setfill(' ') << head->cena << " ||" << setw(8) << setfill(' ') << "gdzie: ";
			if (head->czyNaWynos == 0) {
				cout << " na miejscu \n";
			}
			else {
				cout << " na wynos " << setw(8) << setfill(' ') << " adres: " << head->adres << "\n";
			}
			pause();
			return head;
		}
		head = head->nastepny;
	}
	cout << "Brak zamowien takiej pizzy\n";
	Sleep(1500);
	return nullptr;
}

Pizzeria* czyIstnieje(Pizzeria* head, int nr_zam) {
	while (head) {
		if (head->nr_zam == nr_zam) {
			return head;
		}
		head = head->nastepny;
	}
	return nullptr;
}


void pause() {
	cout << "\n\n\n\nAby kontynuowac wcisnij enter";
	cin.clear();
	cin.ignore(1000, '\n');
}

void blad() {
	cout << "\n\n\n\n\tBLAD, PODAJ POPRAWNA WARTOSC";
	Sleep(1200);
	system("cls");
}

void login() {
	system("cls");
	string haslo = "";
	char ch;
	cout << "\n\n\n\n\n\n\n\t\t\t\t\tSYSTEM LOGOWANIA";
	cout << "\n\n\n\n\n\n\t\t\t\t\tWPROWADZ HASLO: ";
	ch = _getch();
	while (ch != 13) {  //* aby zamaskowac wprowadzane haslo
		haslo.push_back(ch);
		cout << '*';
		ch = _getch();
	}
	if (haslo == "admin") {
		cout << "\n\n\n\n\t\t\tLOGOWANIE POWIODLO SIE | ZAPRASZAMY DO KORZYSTANIA Z PROGRAMU \n\n";
		Sleep(2000);
	}
	else {
		cout << "\n\n\n\n\t\t\tLOGOWANIE NIE POWIODLO SIE | SPROBUJ PONOWNIE\n\n";
		Sleep(2000);
		login();
	}
}

void powitanie() {
	bool kont = true;
	while (kont) {
		system("cls");
		cout << "\n\n====== MENU ======\n\n";
		cout << setw(20) << setfill('=') << "=\n\n";
		cout << "1. LOGOWANIE\n\n";
		cout << "2. INSTRUKCJA\n\n";
		cout << setw(20) << setfill('=') << "=\n\n";
		cout << "TWOJ WYBOR: ";
		int opcja;
		while (!(cin >> opcja && isspace(cin.peek())) || opcja > 2 || opcja < 1) {
			cout << "\nBLAD, PODAJ POPRAWNA WARTOSC: ";
			cin.clear();
			cin.ignore(1000, '\n');
		}
		cin.clear();
		cin.ignore(1000, '\n');

		switch (opcja) {
		case 1:
			login();
			kont = false;
			break;
		case 2:
			system("cls");
			cout << "\n\nProgram umozliwia sprawne zarzadzanie zamowieniami w pizzerii";
			cout << "\nAby korzystac z programu konieczne jest podanie hasla dostepu,\naby uniemozliwic dostep do danych osobom postronnym";
			cout << "\n\nDomyslnie ustawione jest haslo: admin";
			cout << "\n\nPo zalogowaniu uzytkownikowi pokazuje sie menu opcji do zarzadzania zamowieniami";
			cout << "\nProgram umozliwia dodawanie, usuwanie oraz wyszukiwanie";
			cout << "\nzamowien po numerze, lub po pizzy";
			cout << "\nProgram przed zamknieciem pokazuje zarobek danego dnia.";
			cout << "\n\n\nZyczymy przyjemnego korzystania :)\n\n";
			cout << "\n\n\n\nAby kontynuowac wcisnij enter";
			cin.clear();
			cin.ignore(1000, '\n');
		}
	}
}

void plik(int nr2, string pizza, double cena, bool czyNaWynos, string adres) {
	SYSTEMTIME st;
	GetLocalTime(&st);
	fstream plik; //dopisanie do konca pliku danych kolejnego zamowienia
	plik.open("pizzeria.txt", ios::out | ios::app);
	if (plik.is_open()) {
		plik << setw(2) << setfill('0') << st.wHour << ":" << setw(2) << setfill('0') << st.wMinute << "\t" << nr2 
			<< ". Pizza: " << setw(15) << setfill(' ') << pizza << " ||" << setw(8) << setfill(' ')
			<< " cena: " << setw(6) << setfill(' ') << cena << " ||" << setw(8) << setfill(' ') << "gdzie: ";
		if (czyNaWynos == 0) {
			plik << " na miejscu\n";
		}
		else {
			plik << " na wynos  ||" << setw(8) << setfill(' ') << " adres: " << adres << "\n";
		}
		plik.close();
	}
	else
		cout << "Nie udalo sie otworzyc pliku.\n";
}

void usun(Pizzeria*& head, int& nr_zam, double &cenaSuma) {
	cout << "\n";
	if (head == nullptr) { //jesli nie ma zamowien
		cout << "Brak zamowien\n";
	}
	else if (head->poprzedni == nullptr && head->nastepny == nullptr) { //jesli usuwamy jedyne zamowienie
		Pizzeria* tmp = czyIstnieje(head, nr_zam);
		if (tmp) { //jesli istnieje takie zamowienie
			cenaSuma = cenaSuma - tmp->cena;
			cout << "Zamowienie " << tmp->pizza << " zostalo usuniete\n";
			delete head;
			head = nullptr;
		}
		else
			cout << "Brak zamowien o takim id\n";
	}
	else {
		Pizzeria* tmp = czyIstnieje(head, nr_zam);
		if (tmp) { //jesli istnieje
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
			cenaSuma = cenaSuma - tmp->cena;
			cout << "\nZamowienie " << tmp->pizza << " zostalo usuniete\n";
			delete tmp;
		}
		else
			cout << "Brak zamowien o takim id\n";
	}
}

void wypisz(Pizzeria* head) {
	cout << "\n";
	if (head == nullptr)
		cout << "Brak zamowien\n";
	else {
		int ilosc{};
		cout << "Dzisiejsze zamowienia:\n\n";
		while (head) {
			cout << setw(2) << setfill('0') << head->st.wHour << ":" << setw(2) << setfill('0') << head->st.wMinute << "\t" << head->nr_zam << ". Pizza: " << setw(12) << setfill(' ') << head->pizza << " ||" << setw(6) << setfill(' ') 
				<< " cena: " << setw(6) << setfill(' ') << head->cena << " ||" << setw(8) << setfill(' ') << " gdzie: ";
			if (head->czyNaWynos == 0) {
				cout << setw(11) << setfill(' ') << "na miejscu" << endl;
			}
			else {
				cout << setw(11) << setfill(' ') << "na wynos" << " ||" << setw(8) << setfill(' ')
					<< "adres: " << head->adres << "\n";
			}
			head = head->nastepny;
			ilosc++;
		}
		cout << "\n\tIlosc zamowien: " << ilosc;
	}
	pause();
}

void wyczysc(Pizzeria*& head) {
	while (head) {
		Pizzeria* temp = head;
		head = head->nastepny;
		delete temp;
	}
	head = nullptr;
}

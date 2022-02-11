#include<iostream>
#include<string>
#include<windows.h>


using namespace std;


const int plansza_dlugosc = 10;
const int plansza_szerokosc = 10;

int ilosc_b = 8;
int ilosc_c = 8;


struct Figura
{
	char wyglad;
	string kolor;
	bool czy_damka;
};


struct Pole
{
	Figura obiekt;                                                                         //to co stoi wlasnie na tym miejscu
	bool czy_ramka;
	bool czy_zajete;
};


struct Plansza {

	Pole tablica[plansza_dlugosc][plansza_szerokosc];                                      //kazda budka to osobne pole o wlasnych wlasciwociach

	Plansza()
	{
		for (int i = 0; i < plansza_dlugosc; i++)
		{
			tablica[i][0].obiekt.wyglad = '|';
			tablica[0][i].obiekt.wyglad = '-';
			tablica[plansza_szerokosc - 1][i].obiekt.wyglad = '-';
			tablica[i][plansza_dlugosc - 1].obiekt.wyglad = '|';
		}
		tablica[0][plansza_dlugosc - 1].obiekt.wyglad = 't';
		tablica[0][0].obiekt.wyglad = 't';
		tablica[plansza_szerokosc - 1][plansza_dlugosc - 1].obiekt.wyglad = 't';
		tablica[plansza_szerokosc - 1][0].obiekt.wyglad = 't';
		for (int i = 1; i < plansza_dlugosc - 1; i++)
		{
			for (int j = 1; j < plansza_szerokosc - 1; j++)
			{
				tablica[i][j].obiekt.wyglad = '*';
				tablica[i][j].czy_zajete = 0;
			}
		}
		for (int i = 1; i < plansza_dlugosc - 1; i += 2)
		{
			tablica[1][i].obiekt.wyglad = 'B';
			tablica[1][i].czy_zajete = 1;
			tablica[1][i].obiekt.kolor = "biale";
			tablica[1][i].obiekt.czy_damka = 0;

			tablica[2][i + 1].obiekt.wyglad = 'B';
			tablica[2][i + 1].czy_zajete = 1;
			tablica[2][i + 1].obiekt.kolor = "biale";
			tablica[2][i + 1].obiekt.czy_damka = 0;

			//tablica[3][i].obiekt.wyglad = 'B';
			//tablica[3][i].czy_zajete = 1;
			//tablica[3][i].obiekt.kolor = "biale";

			//tablica[6][i + 1].obiekt.wyglad = 'C';
			//tablica[6][i + 1].czy_zajete = 1;
			//tablica[6][i + 1].obiekt.kolor = "czarne";

			tablica[7][i].obiekt.wyglad = 'C';
			tablica[7][i].czy_zajete = 1;
			tablica[7][i].obiekt.kolor = "czarne";
			tablica[7][i].obiekt.czy_damka = 0;


			tablica[8][i + 1].obiekt.wyglad = 'C';
			tablica[8][i + 1].czy_zajete = 1;
			tablica[8][i + 1].obiekt.kolor = "czarne";
			tablica[8][i + 1].obiekt.czy_damka = 0;
		}
	}


	void draw()                                                                                      //ryswoanie planszy
	{
		int k = 0;
		cout << "  ";
		for (int j = 0; j < plansza_szerokosc - 2; j++)
		{
			cout << j + 1 << " ";
		}
		cout << endl;
		for (int i = 0; i < plansza_dlugosc; i++)
		{

			for (int j = 0; j < plansza_szerokosc; j++)
			{
				cout << tablica[i][j].obiekt.wyglad << " ";
			}
			cout << k << endl;
			k++;
		}
	}


	int move(int obecne_x, int obecne_y, int przyszle_x, int przyszle_y)                                //2 koniec ruchu, 1 dalszy ruch, 0 zly ruch
	{
		if (tablica[przyszle_x][przyszle_y].czy_zajete)                                                 //czy mozna bic
		{
			if (tablica[obecne_x][obecne_y].obiekt.kolor == "biale")
			{
				if (obecne_y - przyszle_y == 1)                                                         //biale bija w lewo
				{
					if (!tablica[przyszle_x + 1][przyszle_y - 1].czy_zajete)
					{
						tablica[przyszle_x][przyszle_y] = tablica[przyszle_x + 1][przyszle_y - 1];      //ustawiamy na puste pole
						tablica[przyszle_x + 1][przyszle_y - 1] = tablica[obecne_x][obecne_y];
						tablica[obecne_x][obecne_y] = tablica[przyszle_x][przyszle_y];
						//sprawdzamy czy kolejne bicie mozliwe
						if ((tablica[przyszle_x + 2][przyszle_y - 2].czy_zajete && !tablica[przyszle_x + 3][przyszle_y - 3].czy_zajete)
							|| (tablica[przyszle_x + 2][przyszle_y].czy_zajete && !tablica[przyszle_x + 3][przyszle_y + 1].czy_zajete)
							|| ((tablica[przyszle_x + 2][przyszle_y].czy_zajete || tablica[przyszle_x + 2][przyszle_y - 2].czy_zajete) && (!tablica[przyszle_x + 3][przyszle_y - 3].czy_zajete || !tablica[przyszle_x + 3][przyszle_y + 1].czy_zajete)))
						{
							cout << "mozliwe kolejne bicie, Zbijaj!";
							return 1;
							ilosc_c = ilosc_c - 1;
						}
						ilosc_c = ilosc_c - 1;
						return 2;
					}
				}
				else if (obecne_y - przyszle_y == -1)                                                   //biale bija w prawo
				{
					if (!tablica[przyszle_x + 1][przyszle_y + 1].czy_zajete)
					{
						tablica[przyszle_x][przyszle_y] = tablica[przyszle_x + 1][przyszle_y + 1];     //ustawiamy na puste pole
						tablica[przyszle_x + 1][przyszle_y + 1] = tablica[obecne_x][obecne_y];
						tablica[obecne_x][obecne_y] = tablica[przyszle_x][przyszle_y];
						//sprawdzamy czy kolejne bicie mozliwe
						if ((tablica[przyszle_x + 2][przyszle_y + 2].czy_zajete && !tablica[przyszle_x + 3][przyszle_y + 3].czy_zajete)
							|| (tablica[przyszle_x + 2][przyszle_y].czy_zajete && !tablica[przyszle_x + 3][przyszle_y - 1].czy_zajete)
							|| ((tablica[przyszle_x + 2][przyszle_y].czy_zajete || tablica[przyszle_x + 2][przyszle_y + 2].czy_zajete) && (!tablica[przyszle_x + 3][przyszle_y + 3].czy_zajete || !tablica[przyszle_x + 3][przyszle_y - 1].czy_zajete)))
						{
							cout << "mozliwe kolejne bicie, Zbijaj!";
							return 1;
							ilosc_c = ilosc_c - 1;
						}
						ilosc_c = ilosc_c - 1;
						return 2;
					}
				}
			}
			else if (tablica[obecne_x][obecne_y].obiekt.kolor == "czarne")
			{
				if (obecne_y - przyszle_y == 1)                                                       //czarne bija w lewo
				{
					if (!tablica[przyszle_x - 1][przyszle_y - 1].czy_zajete)
					{
						tablica[przyszle_x][przyszle_y] = tablica[przyszle_x - 1][przyszle_y - 1];    //ustawiamy na puste pole
						tablica[przyszle_x - 1][przyszle_y - 1] = tablica[obecne_x][obecne_y];
						tablica[obecne_x][obecne_y] = tablica[przyszle_x][przyszle_y];
						//sprawdzamy czy kolejne bicie mozliwe
						if ((tablica[przyszle_x - 2][przyszle_y - 2].czy_zajete && !tablica[przyszle_x - 3][przyszle_y - 3].czy_zajete)
							|| (tablica[przyszle_x - 2][przyszle_y].czy_zajete && !tablica[przyszle_x - 3][przyszle_y + 1].czy_zajete)
							|| ((tablica[przyszle_x - 2][przyszle_y - 2].czy_zajete || tablica[przyszle_x - 2][przyszle_y].czy_zajete) && (!tablica[przyszle_x - 3][przyszle_y - 3].czy_zajete || !tablica[przyszle_x - 3][przyszle_y + 1].czy_zajete)))
						{
							cout << "mozliwe kolejne bicie, Zbijaj!";
							return 1;
							ilosc_b = ilosc_b - 1;
						}
						ilosc_b = ilosc_b - 1;
						return 2;
					}
				}
				else//czarne bija w prawo
				{
					if (!tablica[przyszle_x - 1][przyszle_y + 1].czy_zajete)
					{
						tablica[przyszle_x][przyszle_y] = tablica[przyszle_x - 1][przyszle_y + 1];    //ustawiamy na puste pole
						tablica[przyszle_x - 1][przyszle_y + 1] = tablica[obecne_x][obecne_y];
						tablica[obecne_x][obecne_y] = tablica[przyszle_x][przyszle_y];
						//sprawdzamy czy kolejne bicie mozliwe
						if ((tablica[przyszle_x - 2][przyszle_y + 2].czy_zajete && !tablica[przyszle_x - 3][przyszle_y + 3].czy_zajete)
							|| (tablica[przyszle_x - 2][przyszle_y].czy_zajete && !tablica[przyszle_x - 3][przyszle_y - 1].czy_zajete)
							|| ((tablica[przyszle_x - 2][przyszle_y].czy_zajete || tablica[przyszle_x - 2][przyszle_y + 2].czy_zajete) && (!tablica[przyszle_x - 3][przyszle_y + 3].czy_zajete || !tablica[przyszle_x - 3][przyszle_y - 1].czy_zajete)))
						{
							cout << "mozliwe kolejne bicie, Zbijaj!";
							return 1;
							ilosc_b = ilosc_b - 1;
						}
						ilosc_b = ilosc_b - 1;
						return 2;
					}
				}
			}
		}


		else if (tablica[obecne_x][obecne_y].obiekt.kolor == "biale"
			&& obecne_x - przyszle_x == -1
			&& abs(obecne_y - przyszle_y) == 1)
		{
			Pole c = tablica[przyszle_x][przyszle_y];
			tablica[przyszle_x][przyszle_y] = tablica[obecne_x][obecne_y];
			tablica[obecne_x][obecne_y] = c;
			return 2;
		}

		else if (tablica[obecne_x][obecne_y].obiekt.kolor == "czarne"
			&& obecne_x - przyszle_x == 1
			&& abs(obecne_y - przyszle_y) == 1)
		{
			Pole c = tablica[przyszle_x][przyszle_y];
			tablica[przyszle_x][przyszle_y] = tablica[obecne_x][obecne_y];
			tablica[obecne_x][obecne_y] = c;
			return 2;
		}

		else
		{
			return false;
		}
	}
	void wypisz()
	{
		for (int i = 1; i < plansza_dlugosc - 1; i++)
		{
			for (int j = 1; j < plansza_szerokosc - 1; j++)
			{
				cout << tablica[i][j].czy_zajete;
			}
			cout << endl;
		}
	}
};



void licznik() {
	cout << "Ilosc bialych pionkow: " << ilosc_b << " Ilosc czarnych pionkow: " << ilosc_c << endl; //wyswietlanie ilosci pionkow
}


void instrukcja() {
	cout << "1.Zasady sa takie jak w normalnych warcabach( ruch do przodu pionkami po skosie o jedno pole, zbijanie przeciwnika)\n"
		<< "2.Na poczatku podajesz koordynaty(liczba od 1 do 8) w linii pionowej, nastepnie w linii poziomej pionka ktorym\n chcesz sie poruszyc, pozniej analogicznie wybierasz miejsce docelowe pionka.\n "
		<< "3.Nie proboj nielegalnych ruchow graczu\n";
}


int main() {

	Plansza boisko;
	int dlugosc_obecna;
	int dlugosc_przyszla;
	int szerokosc_obecna;
	int szerokosc_przyszla;
	bool tura_gracza_bialego = 1;
	int opcja;

	cout << "Witaj w Warcaby!\n";

	do {
		cout << "Opcja 1: Graj w warcaby\n"
			<< "Opcja 2: Instrukcja\n"
			<< "Opcja 3: Zakoncz\n";

		cin >> opcja;

		switch (opcja)
		{
		case 2: instrukcja();
			break;
		case 3: exit(0);
			break;
		default: cout << "Nie ma takiej opcji gosciu!\n";
			system("cls");
		}
	} while (opcja != 1);



	while (true)
	{
		cout << "Zaczyna bialy, wybierz pionka i wykonaj ruch jak w instrukcji\n";
		boisko.draw();
		licznik();

		while (tura_gracza_bialego)
		{
			cout << "Kolej gracza bialego: ";
			cin >> dlugosc_obecna
				>> szerokosc_obecna
				>> dlugosc_przyszla
				>> szerokosc_przyszla;

			if (boisko.tablica[dlugosc_obecna][szerokosc_obecna].obiekt.kolor == "biale")
			{
				if (boisko.move(dlugosc_obecna, szerokosc_obecna, dlugosc_przyszla, szerokosc_przyszla) == 2)        //koniec ruchu
				{
					tura_gracza_bialego = false;
					system("cls");
					boisko.draw();
					licznik();
				}
			}

			if (ilosc_c == 0)
			{
				cout << "wygrywa bialy!";                                                                           //warunek wygranej
				exit(0);
			}


		}

		while (!tura_gracza_bialego)
		{
			cout << "kolej gracza czarnego: ";
			cin >> dlugosc_obecna
				>> szerokosc_obecna
				>> dlugosc_przyszla
				>> szerokosc_przyszla;
			if (boisko.tablica[dlugosc_obecna][szerokosc_obecna].obiekt.kolor == "czarne")
			{
				if (boisko.move(dlugosc_obecna, szerokosc_obecna, dlugosc_przyszla, szerokosc_przyszla) == 2)           //koniec ruchu
				{
					tura_gracza_bialego = true;
					system("cls");
					boisko.draw();
					licznik();
				}
			}
			if (ilosc_b == 0)
			{
				cout << "wygrywa czarny!";                                                                            //warunek wygranej
				exit(0);
			}
		}

		boisko.move(dlugosc_obecna, szerokosc_obecna, dlugosc_przyszla, szerokosc_przyszla);

		boisko.draw();
		licznik();
		Sleep(100);
		system("cls");
	}

	return 0;

}
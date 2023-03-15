#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <string.h>
#define MAX 128

void wczytanie_alfabetu(char** alfabet, int liczba_liter, int *dlugosci_liter) {
	char napis[MAX];
	bool rozne_dlugosci = false;
	int dlugosc;

	for (int i = 0; i < liczba_liter; i++) {
		scanf(" %s", &napis);
		dlugosci_liter[i] = strlen(napis);
		alfabet[i] = new char[strlen(napis) + 1];
		strncpy(alfabet[i], napis, strlen(napis) + 1);
	}
}

int pozycja_w_alfabecie(char* litera, char** alfabet, int liczba_liter) {
	for (int i = 0; i < liczba_liter; i++) {
		if (!strcmp(alfabet[i], litera)) {
			return i;
		}
	}
	return -1;
}

int pozycja_w_alf(char litera, char* alf, int liczba_liter) {
	for (int i = 0; i < liczba_liter; i++) {
		if (litera == alf[i]) {
			return i;
		}
	}
	return -1;
}

void wczytanie_wirnikow(char** alfabet, int liczba_liter, int** wirniki, int ilosc_wirnikow,
	int* ilosc_l_przesuniecia, int** litery_przesuniecia) {
	char napis[MAX];
	for (int i = 0; i < ilosc_wirnikow; i++) {
		wirniki[i] = new int[liczba_liter];
		for (int j = 0; j < liczba_liter; j++) {
			scanf(" %s", &napis);
			wirniki[i][j] = pozycja_w_alfabecie(napis, alfabet, liczba_liter);
		}
		scanf(" %d", &ilosc_l_przesuniecia[i]);
		if (ilosc_l_przesuniecia[i] > 0) {
			litery_przesuniecia[i] = new int[ilosc_l_przesuniecia[i]];
			for (int k = 0; k < ilosc_l_przesuniecia[i]; k++) {
				scanf(" %s", &napis);
				litery_przesuniecia[i][k] = pozycja_w_alfabecie(napis, alfabet, liczba_liter);
			}
		}
	}
}

void wczytanie_reflektorow(char** alfabet, int liczba_liter, int** reflektory, int ilosc_reflektorow) {
	char napis[MAX];
	for (int i = 0; i < ilosc_reflektorow; i++) {
		reflektory[i] = new int[liczba_liter];
		for (int j = 0; j < liczba_liter; j++) {
			scanf(" %s", &napis);
			reflektory[i][j] = pozycja_w_alfabecie(napis, alfabet, liczba_liter);
		}
	}
}

int sprawdzenie_indeksu(int r, int liczba_liter) {
	if (r > liczba_liter - 1) {
		r -= liczba_liter;
	}
	else if (r < 0) {
		r += liczba_liter;
	}
	return r;
}

int kodowanie_w_wirnikach(int indeks, int liczba_liter, int ilosc_wyb_wir, int** wirniki, int* pozycja_wirnika,
	bool* zmiana_pozycji, int* liczba_liter_wciecia, int** litery_wciecia, int* indeksy_wirnikow) {

	//Wyzerowanie tablicy, która sprawdza, czy wirnik przsunął się
	for (int y = 0; y < ilosc_wyb_wir; y++) {
		zmiana_pozycji[y] = false;
	}

	//Kodowanie litery w wirnikach
	for (int i = 0; i < ilosc_wyb_wir; i++) {
		//Sprawdzenie czy przesunąć pozycję wirników
		if (i == 0) {
			pozycja_wirnika[0]++;
			zmiana_pozycji[0] = true;
		}
		else if (zmiana_pozycji[i - 1]) {
			for (int l = 0; l < liczba_liter_wciecia[indeksy_wirnikow[i - 1]]; l++) {
				if (litery_wciecia[indeksy_wirnikow[i - 1]][l] == pozycja_wirnika[i - 1]) {
					pozycja_wirnika[i]++;
					zmiana_pozycji[i] = true;
				}
			}
		}

		//Kodowanie litery w wirniku
		pozycja_wirnika[i] = sprawdzenie_indeksu(pozycja_wirnika[i], liczba_liter);
		//Przesunięcie litery o pozycję wirnika
		indeks += pozycja_wirnika[i];
		indeks = sprawdzenie_indeksu(indeks, liczba_liter);
		//Odczytanie indeksu litery w wirniku
		indeks = wirniki[indeksy_wirnikow[i]][indeks];
		//Cofnięcie przesunięcia litery w wirniku
		indeks -= pozycja_wirnika[i];
		indeks = sprawdzenie_indeksu(indeks, liczba_liter);

	}

	return indeks;
}

int odwrotne_kodowanie_w_wirnikach(int indeks, int liczba_liter, int ilosc_wyb_wir, int** wirniki, int* pozycja_wirnika, int* indeksy_wirnikow) {
	for (int r = ilosc_wyb_wir - 1; r >= 0; r--) {
		indeks += pozycja_wirnika[r];
		indeks = sprawdzenie_indeksu(indeks, liczba_liter);
		for (int i = 0; i <= liczba_liter; i++) {
			if (indeks == wirniki[indeksy_wirnikow[r]][i]) {
				indeks = i;
				break;
			}
		}
		indeks -= pozycja_wirnika[r];
		indeks = sprawdzenie_indeksu(indeks, liczba_liter);
	}
	return indeks;
}

int main() {
	char** alfabet, *pierwsze_litery, *alf;
	char napis[MAX];
	int liczba_liter, dlugosc_litery, liczba_wirnikow, liczba_reflektorow, indeks;
	int** wirniki, * liczba_liter_przesuniecia, ** litery_przesuniecia, ** reflektory, *dlugosci_liter;
	bool czy_rozna_dlugosc_liter = false;
	/*int liczba_liter, liczba_wirnikow, liczba_reflektorow, indeks, * liczba_liter_przesuniecia, * pozycja_wirnika;
	char litera, kodowanie, **alfabet, ** wirniki, ** litery_przesuniecia, ** reflektory;*/

	int liczba_tekstow, ilosc_wyb_wir, indeks_reflektora;
	int* indeksy_wirnikow, * pozycja_wirnika;

	//Wczytanie alfabetu
	scanf(" %d", &liczba_liter);
	alfabet = new char* [liczba_liter];
	dlugosci_liter = new int[liczba_liter];
	wczytanie_alfabetu(alfabet, liczba_liter, dlugosci_liter);

	alf = new char[liczba_liter + 1];
	for (int i = 0; i < liczba_liter; i++) {
		alf[i] = alfabet[i][0];
	}
	alf[liczba_liter] = '\0';

	//Wczytanie wirników i liter wcięcia
	scanf(" %d", &liczba_wirnikow);
	wirniki = new int* [liczba_wirnikow];
	liczba_liter_przesuniecia = new int[liczba_wirnikow];
	litery_przesuniecia = new int* [liczba_wirnikow];
	wczytanie_wirnikow(alfabet, liczba_liter, wirniki, liczba_wirnikow, liczba_liter_przesuniecia, litery_przesuniecia);

	//Wczytanie reflektorów
	scanf(" %d", &liczba_reflektorow);
	reflektory = new int* [liczba_reflektorow];
	wczytanie_reflektorow(alfabet, liczba_liter, reflektory, liczba_reflektorow);

	bool koduj = true;
	bool* wirnik_zmienil_pozycje;
	scanf(" %d", &liczba_tekstow);
	for (int t = 0; t < liczba_tekstow; t++) {
		scanf(" %d", &ilosc_wyb_wir);
		indeksy_wirnikow = new int[ilosc_wyb_wir];
		pozycja_wirnika = new int[ilosc_wyb_wir];
		wirnik_zmienil_pozycje = new bool[ilosc_wyb_wir];

		for (int j = 0; j < ilosc_wyb_wir; j++) {
			scanf("%d %s", &indeksy_wirnikow[j], &napis);
			pozycja_wirnika[j] = pozycja_w_alfabecie(napis, alfabet, liczba_liter);
			wirnik_zmienil_pozycje[j] = false;
		}
		scanf(" %d", &indeks_reflektora);

		koduj = true;
		char litera = 'a';
		while (koduj) {
			scanf(" %c", &litera);
			if (litera == '$') {
					indeks = -1;
					koduj = false;
					break;
			}

			indeks = pozycja_w_alf(litera, alf, liczba_liter);

			for (int n = 1; n < dlugosci_liter[indeks]; n++) {
				scanf(" %c", &litera);
				if (litera == '$') {
					indeks = -1;
					koduj = false;
					break;
				}
				//napis[n] = litera;
			}
			//napis[dlugosc_litery] = '\0';

			//indeks = pozycja_w_alfabecie(napis, alfabet, liczba_liter);
			if (indeks == -1) {
				continue;
			}

			if (koduj == false) {
				break;
			}

			//Kodowanie w wirniku litery
			indeks = kodowanie_w_wirnikach(indeks, liczba_liter, ilosc_wyb_wir, wirniki, pozycja_wirnika, wirnik_zmienil_pozycje,
				liczba_liter_przesuniecia, litery_przesuniecia, indeksy_wirnikow);

			//Kodowanie w reflektorze
			indeks = reflektory[indeks_reflektora][indeks];

			//Kodowanie powrotne w wirniku
			indeks = odwrotne_kodowanie_w_wirnikach(indeks, liczba_liter, ilosc_wyb_wir, wirniki, pozycja_wirnika, indeksy_wirnikow);

			printf("%s", alfabet[indeks]);
		}
		printf("\n");
		delete[] wirnik_zmienil_pozycje;
		delete[] indeksy_wirnikow;
		delete[] pozycja_wirnika;
	}

	//Usunięcie alfabetu
	for (int i = 0; i < liczba_liter; i++) {
		delete[] alfabet[i];
	}
	delete[] alfabet;
	delete[] alf;
	delete[] dlugosci_liter;

	/*
	//Usunięcie wirników

	for (int i = 0; i < liczba_wirnikow; i++) {
		if (liczba_liter_przesuniecia[i] > 0)
			delete[] litery_przesuniecia[i];
		delete[] wirniki[i];
	}
	delete[] litery_przesuniecia;
	delete[] wirniki;

	delete[] liczba_liter_przesuniecia;

	//Usunięcie reflektorów
	for (int i = 0; i < liczba_reflektorow; i++) {
		delete[] reflektory[i];
	}
	delete[] reflektory;

	*/
	return 0;
}
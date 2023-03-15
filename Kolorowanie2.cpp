#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void wczytanie_macierzy(int** macierz, int liczba_wierzcholkow) {
	for (int i = 0; i < liczba_wierzcholkow; i++) {
		macierz[i] = new int[liczba_wierzcholkow];
		for (int j = 0; j < liczba_wierzcholkow; j++) {
			macierz[i][j] = getchar() - '0';
			//scanf("%1d", &macierz[i][j]);
		}
	}
}

void obliczenie_stopnia_wierzcholkow(int** macierz, int* stopien_wierzcholkow, int liczba_wierzcholkow) {
	for (int i = 0; i < liczba_wierzcholkow; i++) {
		stopien_wierzcholkow[i] = 0;
		for (int j = 0; j < liczba_wierzcholkow; j++) {
			stopien_wierzcholkow[i] += macierz[i][j];
		}
	}
}

bool czy_graf_jest_pelny(int* stopien_wierzcholkow, int liczba_wierzcholkow) {
	int liczba_krawedzi_w_grafie = 0;
	for (int i = 0; i < liczba_wierzcholkow; i++) {
		liczba_krawedzi_w_grafie += stopien_wierzcholkow[i];
	}
	liczba_krawedzi_w_grafie /= 2;
	int liczba_krawedzi_w_grafie_pelnym = (liczba_wierzcholkow * (liczba_wierzcholkow - 1)) / 2;
	if (liczba_krawedzi_w_grafie == liczba_krawedzi_w_grafie_pelnym) {
		return true;
	}
	return false;
}

bool regularnosc_grafu(int* stopnie_wierzcholkow, int liczba_wierzcholkow) {
	int stopien = stopnie_wierzcholkow[0];
	for (int i = 1; i < liczba_wierzcholkow; i++) {
		if (stopien != stopnie_wierzcholkow[i]) {
			return false;
		}
	}
	return true;
}

bool cyklicznosc_grafu(int* stopnie_wierzcholkow, int liczba_wierzcholkow) {
	for (int i = 0; i < liczba_wierzcholkow; i++) {
		if (stopnie_wierzcholkow[i] < 2 || stopnie_wierzcholkow[i] % 2 == 1) {
			return false;
		}
	}
	return true;
}

void usuniecie_macierzy(int** macierz, int liczba_wierzcholkow) {
	for (int i = 0; i < liczba_wierzcholkow; i++) {
		delete[] macierz[i];
	}
}

int main()
{
	int n, liczba_wierzcholkow, **macierz, *stopnie_wierzcholkow, czy_wiekszy;
	scanf("%d", &n);
	while (n--) {
		scanf("%d ", &liczba_wierzcholkow);
		macierz = new int* [liczba_wierzcholkow];
		stopnie_wierzcholkow = new int[liczba_wierzcholkow];

		wczytanie_macierzy(macierz, liczba_wierzcholkow);
		obliczenie_stopnia_wierzcholkow(macierz, stopnie_wierzcholkow, liczba_wierzcholkow);
		czy_wiekszy = false;

		if (czy_graf_jest_pelny(stopnie_wierzcholkow, liczba_wierzcholkow)) {
			czy_wiekszy = true;
		}

		else if (liczba_wierzcholkow % 2 == 0) {
			czy_wiekszy = false;
		}
		else if (!regularnosc_grafu(stopnie_wierzcholkow, liczba_wierzcholkow)) {
			czy_wiekszy = false;
		}
		else {
			if (cyklicznosc_grafu(stopnie_wierzcholkow, liczba_wierzcholkow)) {
				czy_wiekszy = true;
			}
		}

		if (czy_wiekszy) {
			printf("True\n");
		}
		else {
			printf("False\n");
		}

		delete[] stopnie_wierzcholkow;
		usuniecie_macierzy(macierz, liczba_wierzcholkow);
		delete[] macierz;
	}
	return 0;
}
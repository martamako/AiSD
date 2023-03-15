#include "pch.h"
#include <cstdio>

struct osoba {
	int id;
	osoba *next;
	osoba *prev;
};

struct kolko {
	osoba *pierwsza;
	int ile_zyje;
};

void dodaj_osobe(int numer, kolko *sekta) {
	osoba *temp = new osoba;
	temp->id = numer;
	osoba *t = sekta->pierwsza;
	while (t->id != numer - 1) {
		t = t->next;
	}
	temp->prev = t;
	temp->next = sekta->pierwsza;
	sekta->pierwsza->prev = temp;
	t->next = temp;
}

void stworz_sekte(int n, kolko *sekta) {
	sekta->ile_zyje = n;
	osoba *temp = new osoba;
	temp->id = 1;
	temp->next = NULL;
	temp->prev = NULL;
	sekta->pierwsza = temp;

	for (int i = 2; i <= n; i++) {
		dodaj_osobe(i, sekta);
	}
}

void zabij_wszystkich(kolko *sekta) {
	osoba *t = sekta->pierwsza;
	for (int i = 0; i < sekta->ile_zyje; i++) {
		osoba *temp = t->next;
		delete t;
		t = temp;
	}
	sekta->pierwsza = NULL;
}

int zabij_osobe(osoba *martwy, kolko *sekta) {
	int id = 0;
	if (sekta->ile_zyje > 0) {
		if (sekta->ile_zyje >= 3) {
			martwy->prev->next = martwy->next;
			martwy->next->prev = martwy->prev;
			if (martwy == sekta->pierwsza) {
				sekta->pierwsza = martwy->next;
			}
		}
		else if (sekta->ile_zyje == 2) {
			if (martwy->id == sekta->pierwsza->id) {
				sekta->pierwsza = martwy->next;
			}
			sekta->pierwsza->next = NULL;
			sekta->pierwsza->prev = NULL;
		}
		else if (sekta->ile_zyje == 1) {
			sekta->pierwsza = NULL;
		}
		id = martwy->id;
		delete martwy;
		sekta->ile_zyje--;
	}
	return id;
}

int morderstwo(int k, kolko *sekta) {
	int numer_zabitego = 0, kiedy = 1, zwroc = 1;
	bool znaleziony = false;
	osoba *t = NULL;
	if (sekta->ile_zyje == 1) {
		t = sekta->pierwsza;
	}
	if (sekta->ile_zyje >= 2) {
		t = sekta->pierwsza->next;
	}
	while (sekta->ile_zyje) {
		if (sekta->ile_zyje == 1) {
			numer_zabitego = zabij_osobe(t, sekta);
		}
		else {
			osoba *temp = t->next;
			numer_zabitego = zabij_osobe(t, sekta);
			if (sekta->ile_zyje > 1) {
				t = temp;
				t = t->next;
			}
			else {
				t = sekta->pierwsza;
			}
		}
		if (znaleziony == false) {
			if (kiedy == k) {
				znaleziony = true;
				zwroc = numer_zabitego;
				zabij_wszystkich(sekta);
				return zwroc;
			}
			else {
				kiedy++;
			}
		}
	}
	return zwroc;
}


int main()
{
	int ile_testow, n, k;
	scanf_s("%d\n", &ile_testow);
	while (ile_testow--) {	
		scanf_s("%d %d", &n, &k);
		if (n > 0) {
			kolko *sekta = new kolko;
			stworz_sekte(n, sekta);
			if (k < 0) {
				k += n + 1;
			}
			printf("%d\n", morderstwo(k, sekta));
			delete sekta;
			sekta = NULL;
		}
	}
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Osoba* Pozicija;
typedef struct Osoba {
	char ime[20];
	char prezime[20];
	int g_r;
	Pozicija Next;
}osoba;

int UnosNaPocetak(const char name[20], const char surname[20], int birthYear, Pozicija position);
int Ispis(Pozicija position);
int UnosNaKraj(const char name[20], const char surname[20], int birthYear, Pozicija position);
int Trazi(const char surname[20], Pozicija position);
int Brisi(const char name[20], Pozicija position);
int dodajIza(const char name[20], const char surname[20], int birthYear, const char targetName[20], const char targetSurname[20], Pozicija position);
int dodajIspred(const char name[20], const char surname[20], int birthYear, const char targetName[20], const char targetSurname[20], Pozicija position);
int sortiraj(Pozicija position);
int unosUDatoteku(Pozicija position);
int citanjeIzDatoteke(Pozicija position);

int main() {
	osoba Head;
	Head.Next = NULL;
	UnosNaPocetak("Mate", "Matic", 2000, &Head);
	Ispis(Head.Next);
	printf("\n");
	UnosNaKraj("Jure", "Juric", 2001, &Head);
	Ispis(Head.Next);
	printf("\n");
	UnosNaPocetak("Stipe", "Stipic", 2000, &Head);
	Ispis(Head.Next);
	printf("\n");
	UnosNaKraj("Ana", "Anic", 2000, &Head);
	Ispis(Head.Next);
	printf("\n");
	Trazi("Juric", Head.Next);
	Brisi("Ana", &Head);
	Ispis(Head.Next);
	printf("\n");
	dodajIspred("Ivan", "Ivic", 2000, "Jure", "Juric", &Head);
	Ispis(Head.Next);
	printf("\n");
	dodajIza("Luka", "Lukic", 2000, "Jure", "Juric", &Head);
	Ispis(Head.Next);
	printf("\n");
	sortiraj(&Head);
	Ispis(Head.Next);
	printf("\n");
	unosUDatoteku(Head.Next);
	printf("Sadrzaj datoteke:\n");
	citanjeIzDatoteke(Head.Next);
	printf("\nLista nakon citanja:\n");
	Ispis(Head.Next);
	while (Head.Next != NULL) {
		Pozicija q = Head.Next;
		Head.Next = q->Next;
		free(q);
	}
	return 0;
}

int unosUDatoteku(Pozicija position) {
	FILE* fp = NULL;
	fp = fopen("osobe.txt", "w");
	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke.\n");
		return -1;
	}
	while (position != NULL) {
		fprintf(fp, "%s %s %d\n", position->ime, position->prezime, position->g_r);
		position = position->Next;
	}
	fclose(fp);
	return 0;
}

int citanjeIzDatoteke(Pozicija position)
{
	FILE* fp = fopen("osobe.txt", "r");
	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke.\n");
		return -1;
	}
	Pozicija q;
	while (1) {
		q = (Pozicija)malloc(sizeof(struct Osoba));

		if (q == NULL) {
			printf("Neuspjesna alokacija memorije.\n");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%19s %19s %d",
			q->ime, q->prezime, &q->g_r) != 3) {
			free(q);
			break;
		}
		q->Next = NULL;
		while (position->Next != NULL)
			position = position->Next;
		position->Next = q;
		position = q;
	}
	fclose(fp);
	return 0;
}

int sortiraj(Pozicija position) {
	Pozicija q, temp;
	while (position->Next != NULL && position->Next->Next != NULL) {
		q = position->Next->Next;
		if (_strcmpi(position->prezime, q->prezime) > 0) {
			temp = position->Next;
			temp->Next = q->Next;
			q->Next = temp;
			position->Next = q;
		}
		position = position->Next;
	}
	return 0;
}

int dodajIza(const char name[20], const char surname[20], int birthYear, const char targetName[20], const char targetSurname[20], Pozicija position) {
	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct Osoba));
	if (q == NULL) {
		printf("Greska pri alokaciji memorije!\n");
		return 1;
	}
	while (position->Next != NULL && (_strcmpi(position->Next->ime, targetName) != 0 || _strcmpi(position->Next->prezime, targetSurname) != 0))
		position = position->Next;
	if (position->Next == NULL) {
		printf("Osoba pod imenom %s i prezimenom %s ne postoji u listi.\n", targetName, targetSurname);
		return 1;
	}
	strcpy_s(q->ime, sizeof(q->ime), name);
	strcpy_s(q->prezime, sizeof(q->prezime), surname);
	q->g_r = birthYear;
	q->Next = position->Next->Next;
	position->Next->Next = q;

	return 0;
}

int dodajIspred(const char name[20], const char surname[20], int birthYear, const char targetName[20], const char targetSurname[20], Pozicija position) {
	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct Osoba));
	if (q == NULL) {
		printf("Greska pri alokaciji memorije!\n");
		return 1;
	}
	while (position->Next != NULL && (_strcmpi(position->Next->ime, targetName) != 0 || _strcmpi(position->Next->prezime, targetSurname) != 0))
		position = position->Next;
	if (position->Next == NULL) {
		printf("Osoba pod imenom %s i prezimenom %s ne postoji u listi.\n", targetName, targetSurname);
		return 1;
	}
	strcpy_s(q->ime, sizeof(q->ime), name);
	strcpy_s(q->prezime, sizeof(q->prezime), surname);
	q->g_r = birthYear;
	q->Next = position->Next;
	position->Next = q;

	return 0;
}

int UnosNaPocetak(const char name[20], const char surname[20], int birthYear, Pozicija position) {
	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct Osoba));
	if (q == NULL) {
		printf("Greska pri alokaciji memorije!\n");
		return 1;
	}
	strcpy_s(q->ime, sizeof(q->ime), name);
	strcpy_s(q->prezime, sizeof(q->prezime), surname);
	q->g_r = birthYear;
	q->Next = position->Next;
	position->Next = q;
	return 0;
}

int UnosNaKraj(const char name[20], const char surname[20], int birthYear, Pozicija position) {
	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct Osoba));
	if (q == NULL) {
		printf("Greska pri alokaciji memorije!\n");
		return 1;
	}
	while (position->Next != NULL)
		position = position->Next;

	strcpy_s(q->ime, sizeof(q->ime), name);
	strcpy_s(q->prezime, sizeof(q->prezime), surname);
	q->g_r = birthYear;
	q->Next = position->Next;
	position->Next = q;

	return 0;
}

int Trazi(const char surname[20], Pozicija position) {
	while (position != NULL && (_strcmpi(position->prezime, surname) != 0))
		position = position->Next;
	if (position == NULL) {
		printf("Osoba pod prezimenom %s ne postoji u listi.\n", surname);
	}
	else if (_strcmpi(position->prezime, surname) == 0) {
		printf("Pronadena osoba pod prezimenom %s je: %s %s %d\n", surname, position->ime, position->prezime, position->g_r);
	}
	return 0;
}

int Brisi(const char name[20], Pozicija position) {
	Pozicija q;
	while (position->Next != NULL && (_strcmpi(position->Next->ime, name) != 0)) {
		position = position->Next;
	}
	if (position == NULL) {
		printf("Osoba pod prezimenom %s ne postoji u listi.\n", name);
	}
	else if (_strcmpi(position->Next->ime, name) == 0) {
		q = position->Next;
		position->Next = q->Next;
		free(q);
	}
	return 0;
}

int Ispis(Pozicija position) {
	while (position != NULL) {
		printf("%s %s %d\n", position->ime, position->prezime, position->g_r);
		position = position->Next;
	}
	return 0;
}

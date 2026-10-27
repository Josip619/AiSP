/*Definirati strukturu osoba (ime, prezime, godina roðenja) i napisati program koji:
a) dinamièki dodaje novi element na poèetak liste,
b) ispisuje listu,
c) dinamièki dodaje novi element na kraj liste,
d) pronalazi element u listi (po prezimenu),
e) briše odreðeni element iz liste.
U zadatku se ne smiju koristiti globalne varijable.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Osoba* Pozicija;

typedef struct Osoba {
    char ime[50];
    char prezime[50];
    int dob;
    Pozicija Next;
} osoba;


int unesiPrvu(const char*, const char*, int, Pozicija);
int ispis(Pozicija);
int unesiZadnju(const char*, const char*, int, Pozicija);
int trazi(const char*, Pozicija);
int brisi(const char*, Pozicija);

int main() {
    osoba Head;
    Head.Next = NULL;

    unesiPrvu("Ante", "Antic", 2001, &Head);
    ispis(Head.Next);
    printf("\n");

    unesiZadnju("Marko", "Markovic", 1998, &Head);
    ispis(Head.Next);
    printf("\n");

    unesiPrvu("Marija", "Maric", 1991, &Head);
    ispis(Head.Next);
    printf("\n");

    unesiPrvu("Ana", "Anic", 2007, &Head);
    ispis(Head.Next);
    printf("\n");

    trazi("Maric", Head.Next);
    printf("\n\n");

    brisi("Marko", Head.Next); 
    ispis(Head.Next);
    printf("\n");

    return 0;
}

int unesiPrvu(const char* name, const char* surname, int yob, Pozicija p) {
    Pozicija q = (Pozicija)malloc(sizeof(struct Osoba));

    if (q == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return -1;
    }

    strcpy_s(q->ime, sizeof(q->ime), name);
    strcpy_s(q->prezime, sizeof(q->prezime), surname);
    q->dob = yob;

   
    q->Next = p->Next;
    p->Next = q;

    return 0;
}

int ispis(Pozicija p) {
    while (p != NULL) {
        printf("%s %s, %d ", p->ime, p->prezime, p->dob);
        p = p->Next; 
    }
    return 0;
}

int unesiZadnju(const char* name, const char* surname, int yob, Pozicija p) {
    Pozicija q = (Pozicija)malloc(sizeof(struct Osoba));

    if (q == NULL) {
        printf("Neuspjesna alokacija!\n");
        return -1;
    }

    while (p->Next != NULL) {
        p = p->Next;
    }

    strcpy_s(q->ime, sizeof(q->ime), name);
    strcpy_s(q->prezime, sizeof(q->prezime), surname);
    q->dob = yob;

    q->Next = NULL;
    p->Next = q;

    return 0;
}

int trazi(const char* surname, Pozicija p) {
    while (p != NULL && (_strcmpi(p->prezime, surname) != 0)) {
        p = p->Next;
    }
    if (p == NULL) {
        printf("Osoba pod prezimenom %s ne postoji na listi\n", surname);
    }
    else {
        printf("Pronadjena je osoba: %s %s %d", p->ime, p->prezime, p->dob);
    }

    return 0;
}

int brisi(const char* name, Pozicija p) {
    Pozicija q;

    while (p->Next != NULL && (_strcmpi(p->Next->ime, name) != 0)) {
        p = p->Next;
    }

    if (p->Next == NULL) {
        printf("Osoba pod ovim imenom ne postoji\n");
    }
    else {
        q = p->Next;
        p->Next = q->Next;
        free(q); 
    }
    return 0;
}


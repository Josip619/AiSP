/*3. Prethodnom zadatku dodati funkcije:
a) dinamički dodaje novi element iza određenog elementa,
b) dinamički dodaje novi element ispred određenog elementa,
c) sortira listu po prezimenima osoba,
d) upisuje listu u datoteku,
e) čita listu iz datoteke. */


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
int dodajIza(const char*, const char*, int, const char*, const char*, Pozicija);
int dodajIspred(const char*, const char*, int, const char*, const char*, Pozicija);
int sortiraj(Pozicija);
int unosFile(Pozicija);
int citaFile(Pozicija);


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

    dodajIspred("Mate", "Matic", 2000, "Ante", "Antic", &Head);
    ispis(Head.Next);
    printf("\n");
    dodajIza("Stipe", "Stipic", 2000, "Ante", "Antic", &Head);
    ispis(Head.Next);

    printf("\n");

    sortiraj(&Head);

    printf("\n");

    ispis(Head.Next);

    printf("\n");

    unosFile(Head.Next);

    citaFile(&Head);

    printf("\nLista nakon citanja:\n");

    ispis(Head.Next);

    while (Head.Next != NULL) {
        Pozicija q = Head.Next;
        Head.Next = q->Next;
        free(q);
    }


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

int dodajIza(const char* name, const char* surname, int year, const char* name1, const char* surname1, Pozicija p) {
    Pozicija q = (Pozicija)malloc(sizeof(struct Osoba));

    if (q == NULL) {
        printf("Greska pri alokaciji memorije\n");
        return -1;
    }

    while (p->Next != NULL && (_strcmpi(p->Next->ime, name1) != 0 || _strcmpi(p->Next->prezime, surname1) != 0)) {
        p = p->Next;
    }

    if (p->Next == NULL) {
        printf("Osoba pod imenom %s i prezimenom %s ne postoji u listi.\n", name1, surname1);
        free(q);
        return 1;
    }

    strcpy_s(q->ime, sizeof(q->ime), name);
    strcpy_s(q->prezime, sizeof(q->prezime), surname);
    q->dob = year;

    q->Next = p->Next->Next;
    p->Next->Next = q;

    return 0;
}

int dodajIspred(const char* name, const char* surname, int year, const char* name1, const char* surname1, Pozicija p) {
    Pozicija q = (Pozicija)malloc(sizeof(struct Osoba));
    if (q == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return -1;
    }

    while (p->Next != NULL && (_strcmpi(p->Next->ime, name1) != 0 || _strcmpi(p->Next->prezime, surname1) != 0)) {
        p = p->Next;
    }

    if (p->Next == NULL) {
        printf("Osoba pod imenom %s i prezimenom %s ne postoji u listi.\n", name1, surname1);
        free(q);
        return 1;
    }

    strcpy_s(q->ime, sizeof(q->ime), name);
    strcpy_s(q->prezime, sizeof(q->prezime), surname);
    q->dob = year;

    q->Next = p->Next;
    p->Next = q;

    return 0;
}
int sortiraj(Pozicija p) {
    if (p == NULL || p->Next == NULL) {
        return -1;
    }

    Pozicija i, j;
    char tempIme[50], tempPrezime[50];
    int tempDob;

    i = p->Next;
    while (i != NULL) {
        j = i->Next;
        while (j != NULL) {
            if (_strcmpi(i->prezime, j->prezime) > 0 || (_strcmpi(i->prezime, j->prezime) == 0 && _strcmpi(i->ime, j->ime) > 0)) {

                strcpy_s(tempIme, sizeof(tempIme), i->ime);
                strcpy_s(tempPrezime, sizeof(tempPrezime), i->prezime);
                tempDob = i->dob;

                strcpy_s(i->ime, sizeof(i->ime), j->ime);
                strcpy_s(i->prezime, sizeof(i->prezime), j->prezime);       //Treba rijesiti preko pokazivaca
                i->dob = j->dob;

                strcpy_s(j->ime, sizeof(j->ime), tempIme);
                strcpy_s(j->prezime, sizeof(j->prezime), tempPrezime);
                j->dob = tempDob;
            }
            j = j->Next;
        }
        i = i->Next;
    }

    return 0;
}

int unosFile(Pozicija p) {
    FILE* fp = fopen("osobe.txt", "w");
    if (fp == NULL) {
        printf("Greska kod otvaranja datoteke\n");
        return -1;
    }

    while (p != NULL) {
        fprintf(fp, "%s %s %d\n", p->ime, p->prezime, p->dob);
        p = p->Next;
    }

    fclose(fp);
    return 0;
}

int citaFile(Pozicija p) { 
    FILE* fp = fopen("osobe.txt", "r");
    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke.\n");
        return -1;
    }

    while (1) {
        Pozicija q = (Pozicija)malloc(sizeof(struct Osoba));
        if (q == NULL) {
            printf("Neuspjesna alokacija memorije.\n");
            fclose(fp);
            return -1;
        }

        if (fscanf(fp, "%49s %49s %d", q->ime, q->prezime, &(q->dob)) != 3) {
            free(q);
            break;
        }

        q->Next = NULL;
        while (p->Next != NULL) {
            p = p->Next;
        }
        p->Next = q;
        p = q;
    }

    fclose(fp);
    return 0;
}








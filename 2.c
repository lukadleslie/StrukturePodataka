#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME (256)

struct person;
typedef struct person *Position;
typedef struct person {
	char ime[MAX_NAME];
	char prezime[MAX_NAME];
	int birthYear;
	Position next;
} Person;

Position createStudent(char*, char*, int);
void printList(Position);
void unosPocetak(Position, Position);
void unosKraj(Position, Position);
Position pronalazak(Position, char*);
Position pronalazakPret(Position, char*);
void brisi(Position, char*);

int main(void) {

	Position head = NULL, p, n;
	char firstName[MAX_NAME], lastName[MAX_NAME], prezimen[MAX_NAME];
	int birthYear;
	char s;

	while (1) {

		printf("Novi element:\tA - na pocetak\tB - na kraju\nC - Pronalazak elemenata\nD - Obrisati element\nE - Kraj programa\n");
		scanf(" %c", &s);
		switch (s) {
            case 'A' : 
            case 'a':
                printf("unesite ime: ");
                scanf(" %s", firstName);

                printf("unesite prezime: ");
                scanf(" %s", lastName);

                printf("unesite godinu rodjenja: ");
                scanf(" %d", &birthYear);

                printf("\n");

                p = createStudent(firstName, lastName, birthYear);
                unosPocetak(&head, p);
                printList(&head);
                break;
            case 'B':
            case 'b':
                printf("unesite ime: ");
                scanf(" %s", firstName);

                printf("unesite prezime: ");
                scanf(" %s", lastName);

                printf("unesite godinu rodjenja: ");
                scanf(" %d", &birthYear);

                printf("\n");

                p = createStudent(firstName, lastName, birthYear);
                unosKraj(&head, p);
                printList(&head);
                break;
            case 'C':
            case 'c':
                printf("unesite prezime studenta koje zelite naci: ");
                scanf(" %s", prezimen);
                n = pronalazak(&head, prezimen);
                printf("\n%s %s %d\r\n", n->ime, n->prezime, n->birthYear);
                break;
            case 'D':
            case 'd':

                printf("unesite prezime studenta koje zelite izbrisati: ");
                scanf(" %s", prezimen);
                brisi(&head, prezimen);
                printList(&head);
                break;
            case 'E':
            case 'e':
                return 0;
                break;
            }  
        }

        return 0;
    }

Position createStudent(char* firstName, char* lastName, int birthYear)
    {
        Position p;

        p = (Position)malloc(sizeof(struct person));

        p->birthYear = birthYear;
        strcpy(p->ime, firstName);
        strcpy(p->prezime, lastName);
        p->next = NULL;

        return p;
    }
void printList(Position head)
    {
        Position p = NULL;

        printf("KONTENT LISTE: \n\n");
        for (p = head->next; p != NULL; p = p->next) {
            printf("\t %s %s %d \n", p->ime, p->prezime, p->birthYear);
        }
        printf("\r\n");
    }

void unosPocetak(Position head, Position p)
    {
        p->next = head->next;
        head->next = p;
    }

void unosKraj(Position q, Position p)
    {
        while (q->next != NULL) {
            q = q->next;
        }
        unosPocetak(q, p);
    }

Position pronalazak(Position q, char* prez) {
	while (q->next != NULL && strcmp(q->prezime, prez))
		q = q->next;
	return q;
}

Position pronalazakPret(Position p, char *prezimen) {
	Position pret = p;
	p = p->next;

	while (p->next != NULL && strcmp(p->prezime, prezimen)) {
		pret = p;
		p = p->next;
	}
	if (p->next == NULL) {
		printf("\nne postoji!\n\n");
		return NULL;
	}
	return pret;
}

void brisi(Position p, char *prezimen) {
	Position prev;
	prev = pronalazakPret(p, prezimen);

	if (prev != NULL) {
		p = prev->next;
		prev->next = p->next;
		free(p);
	}
}


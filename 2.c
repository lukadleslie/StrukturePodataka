#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD (256)

typedef struct person node;
struct person{
    char ime[MAX_WORD];
    char prez[MAX_WORD];
    int godina;
    struct person *next;
};

void unos(char *, char *, int *);
node *napravi_node(char *, char*, int *);
node *dodaj_na_pocetku(node **, node *);
node *dodaj_na_kraju(node **, node *);
void ispis(node *);
node *pronalazi_element(node *, char [MAX_WORD]);
int usporedi(char [MAX_WORD], char [MAX_WORD]);
void erase(node **, node *);

int main()
{
    node *head = NULL;
    node *n;
    int z;
    char x[MAX_WORD], y[MAX_WORD], c, ime[MAX_WORD];

    do{
        printf("\nA - dodaj nova osoba na pocetku liste\nB - ispisati listu\nC - Dodaj osobu na kraju liste\nD - Pretrazi osobu po prezimenu\nE - Obrisati osobu iz liste\nQ - quit program\n\n");

        scanf(" %c", &c);

        switch(c){
            case 'A':
            case 'a':
                unos(x, y, &z);
                n = napravi_node(x,y,&z);
                dodaj_na_pocetku(&head, n);
                break;
            case 'B':
            case 'b':
                if(head == NULL){
                    printf("\nList je prazan...\n\n");
                    break;
                }
                printf("\n");
                ispis(head);
                break;
            case 'C':
            case 'c':
                unos(x, y, &z);
                n = napravi_node(x,y,&z);
                dodaj_na_kraju(&head, n);
                break;
            case 'D':
            case 'd':
                if(head == NULL){
                    printf("\nList je prazan...\n\n");
                    break;
                }
                printf("Unesite prezime: ");
                scanf(" %s", x);
                n = pronalazi_element(head, x);
                printf("/*\t%s %s\t%d\t*/\n", n->ime, n->prez, n->godina);
                break;
            case 'E':
            case 'e':
                printf("\nUnesite prezime: ");
                scanf(" %s", x);
                n = pronalazi_element(head, x);
                erase(&head, n);
                break;
            case 'Q':
            case 'q':
                continue;
            default:
                printf("\nPonovno unesite odabir:\n\n");
                break;
        }

    }while(c != 'q' && c != 'Q');


    return 0;
}
void unos(char *x, char *y, int *z)
{
   printf("\nUnesi ime: ");
   scanf(" %s", x);
   printf("Unesi prezime: ");
   scanf(" %s", y);
   printf("Unesi godinu rodenja: ");
   scanf(" %d", z);
}
node *napravi_node(char *x, char*y, int *z)
{
    node *tmp = malloc(sizeof(node));
    strcpy(tmp->ime, x);
    strcpy(tmp->prez, y);
    tmp->godina = *z;
    tmp->next = NULL;

    return tmp;
}
void ispis(node *head)
{
    node *tmp = head;

    while(tmp != NULL){
        printf("/*\t%s %s\t%d\t*/\n", tmp->ime, tmp->prez, tmp->godina);
        tmp = tmp->next;
    } 
}
node *dodaj_na_pocetku(node **head, node *n)
{
    n->next = *head;
    *head = n;
    return n;
}
node *dodaj_na_kraju(node **head, node *n)
{
    if(*head == NULL)
        dodaj_na_pocetku(head, n);
    else{
        node *tmp = *head;
        while(tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = n;
        n->next = NULL;
    }

    return n;
}
node *pronalazi_element(node *head, char ime[MAX_WORD])
{
    int br = 0;
    node *n;
    for(node *tmp = head; tmp != NULL; tmp = tmp->next){
        if(usporedi(tmp->prez, ime) && strlen(tmp->prez) == strlen(ime)){
            n = tmp;         
            br++;
        }
    }    
        if(br > 1)
            printf("\n\nMore than one person matched your search..\n");
        else if(br == 0)
            printf("\n\nNo items matched your query...\n");

        return n;
}
int usporedi(char str[MAX_WORD],char str2[MAX_WORD])
{
    for(int i = 0; str[i]; i++){
        if(tolower(str[i]) == tolower(str2[i]))
            continue;
        else
            return 0;
    }
    return 1;
}
void erase(node **head, node *n)
{
    node *tmp = *head;

    if(*head == n){
        *head = n->next;
        free(n);
        return;
    }

    while(tmp->next != n)
        tmp = tmp->next;

    tmp->next = tmp->next->next;
    free(n);
    return;
}

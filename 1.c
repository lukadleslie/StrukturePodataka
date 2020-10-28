#include <stdio.h>
#include <stdlib.h>

typedef struct {
char ime[10];
char prezime[10];
int bodovi;
} Student;

Student unos(FILE *, int);
int pribroji(FILE *);
float relativ(int, int);

int main()
{
    int max;
    FILE *ptr;
    ptr = fopen("rez.txt", "r");

    printf("Unesite max broj bodova: ");
    scanf("%d", &max);
    printf("Ime Prezime\tApsolutni:\tRelativni:\n");
    unos(ptr, max);

    return 0;
}
Student unos(FILE *ptr, int max)
{
    int br = pribroji(ptr);
    Student *s;
    s = (Student *)malloc(br * sizeof(Student));

    for (int i = 0; i < br; i++)
    {
        fscanf(ptr, "%s %s %d", s[i].ime, s[i].prezime, &s[i].bodovi);
        printf("%s %s\t%d\t\t%.2f %%\n", s[i].ime, s[i].prezime, s[i].bodovi, relativ(s[i].bodovi, max));
    }

    fclose(ptr);
    return *s;
}
int pribroji(FILE *ptr)
{
    int br = 0;
    char a,c;

    while ((c = fgetc(ptr)) != EOF)
    {
        if (c == '\n')
        br++;
        a = c;
    }
    if(a != 10)
        br++;

    rewind(ptr);

    return br;
}
float relativ(int br, int max)
{    
    float x = (float)br/max*100;
    return x;
}

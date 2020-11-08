#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD (256)

typedef struct poly *poly_ptr;
typedef struct poly{
    int coeff;
    int exp;
    poly_ptr next; 
} poly;

poly read_data(poly_ptr, char *);
poly add(poly_ptr, poly_ptr, poly_ptr);
poly mult(poly_ptr, poly_ptr, poly_ptr);
void print_list(poly_ptr); 

int main(void)
{
    char dat_1[MAX_WORD] = "datoteke/coeff.txt"; 
    char dat_2[MAX_WORD] = "datoteke/exp.txt";
    int i = 0;

    poly p1, p2, zbr, pro;
    p1.next = NULL, p2.next = NULL, zbr.next = NULL, pro.next = NULL;

    p1 = read_data(&p1, dat_1);
    p2 = read_data(&p2, dat_2);

    zbr = add(&p1, &p2, &zbr);
    //pro = mult(&p1, &p2, &pro);
    
    //printf("%p\n", zbr.next);

    print_list(&zbr);
    //printf("\n");
    //print_list(&pro);
    //printf("\n");

    return 0;
}
poly read_data(poly_ptr n, char *dat)
{
    poly_ptr temp;

    FILE *ptr = NULL;
    ptr = fopen(dat, "r");

    while(!feof(ptr)){
        temp = (poly_ptr)malloc(sizeof(poly));
        fscanf(ptr, " %d %d", &temp->coeff, &temp->exp);
        temp->next = n->next;
        n->next = temp;
    }

    fclose(ptr); 
    return *n;
}
poly add(poly_ptr p1, poly_ptr p2, poly_ptr zbr)
{
    poly_ptr temp;
    poly_ptr p2_head = p2->next;
    p1 = p1->next;
    p2 = p2->next;

    while(p1 != NULL){
        while(p2 != NULL){
            if(p1->exp == p2->exp){
                temp = (poly_ptr)malloc(sizeof(poly));
                temp->exp = p1->exp; 
                temp->coeff = p1->coeff + p2->coeff;
                temp->next = zbr->next;
                zbr->next = temp;
           }
            p2 = p2->next;
        }
        p1 = p1->next;
        p2 = p2_head;
    }

    return *zbr; 
}
poly mult(poly_ptr p1, poly_ptr p2, poly_ptr pro)
{
    poly_ptr temp;
    temp->next = NULL;
    poly_ptr p2_head = p2;
    int i = 0;

    while(p1->next != NULL){
        while(p2->next != NULL){
            printf("%d: %dx^%d\t%dx^%d\n", i+1, p1->next->coeff, p1->next->exp, p2->next->coeff, p2->next->exp);
            temp = (poly_ptr)malloc(sizeof(poly));
            temp->coeff = p1->next->coeff * p2->next->coeff;
            temp->exp = p1->next->exp + p2->next->exp;
            temp->next = pro->next;
            pro->next = temp;

            p2 = p2->next;
            printf("%d %d\n", temp->coeff, temp->exp);
        }
        i++;
        p1 = p1->next;
        p2 = p2_head;
    }

    return *pro;
}
void print_list(poly_ptr p)
{
    while(p->next != NULL){
        printf("%d %d\n", p->next->coeff, p->next->exp);
        p = p->next;
    /*
        if(!i)
            printf(" + ");
        if(p->next->exp == 1)
            printf("(%dx)", p->next->coeff);
        else if(!p->next->exp)
            printf("(%d)", p->next->coeff);
        else
            printf("(%dx)^%d", p->next->coeff, p->next->exp);

        p = p->next;
        i++; 
    */
    }
}

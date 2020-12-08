#include <stdio.h>
#include <stdlib.h>

typedef struct list *list_ptr;
typedef struct list {
    int el;
    char op;
    list_ptr next;
} list;

void pop_stog(list_ptr);
void pop_to_postfix(list_ptr, list_ptr, int);
void postfix(list_ptr, list_ptr, int);
void pop(list_ptr, int);
void push_int(list_ptr, int, int*);
void push_char(list_ptr, int);
void push_end(list_ptr, list_ptr);
void reverse_print(list_ptr);
void parantheses(list_ptr, list_ptr);
int izracun(list_ptr, list_ptr);
int racun(char, int, int);
int is_operator(int);
int is_number(int);
int print(list_ptr);

int main(void)
{
    int c, a = 0, b = 0, *d;
    list stack, stack2, post;
    stack.next = NULL, stack2.next = NULL, post.next = NULL;

    FILE* ptr = fopen("datoteke/infix.txt", "r+");

    while (!(feof(ptr))) {
        c = fgetc(ptr);
        if (is_number(c)){
            push_int(&post, c-48, &a); //pushes input to the postfix equation if a number is read
            a = 1;
        }
        else if (is_operator(c)){
            a = 0;
            push_char(&stack, c); //pushes character to stack if a operator is read
            postfix(&post, &stack, c); //pops operator to postfix equation when necessary
        }
        else
            a = 0;
    }

    push_end(&post, &stack); //pops remaining operators from stack -> postfix eq. when last number is read
    printf("Postfix izraz: ");                                          
    reverse_print(post.next); //recursive function to print the postfix equation
    printf("\n");
    
    printf("Rezultat: %d\n", izracun(post.next, &stack2)); //calculates the postfix equation

    fclose(ptr);
    return 0;
}
void pop_stog(list_ptr ptr)
{
    list_ptr temp = ptr->next;
    ptr->next = ptr->next->next;    
    free(temp);
}
int izracun(list_ptr post, list_ptr stog)
{
    int el = 0;
    list_ptr temp, stog_ptr, ptr = post;
    if(ptr == NULL)
        return el;
    izracun(ptr->next, stog);
    if(ptr->op == '\0'){
        temp = malloc(sizeof(list));
        temp->el = ptr->el;
        temp->op = '\0';
        temp->next = stog->next;
        stog->next = temp;
    }
    else{
        if(stog->next != NULL){
            stog_ptr = stog->next;
            if(stog_ptr->next != NULL){
                el = racun(ptr->op, stog->next->el, stog->next->next->el);
                stog->next->next->el = el;
                pop_stog(stog);
            }
            else
                return el;
        }
        else
            return el;
    }
    return el;
}
void reverse_print(list_ptr ptr)
{
    if(ptr == NULL)
        return;
    reverse_print(ptr->next);
    if(ptr->op != '\0')
        printf("%c  ", ptr->op);
    else
        printf("%d ", ptr->el);
}
int racun(char c, int y, int x)
{
    switch(c){
        case '*':
            return(x*y);
            break;
        case '/':
            return(x/y);
            break;
        case '+':
            return(x+y);
            break;
        case '-':
            return(x-y);
            break;
        default:
            return -1;
    }
}
void postfix(list_ptr post, list_ptr stack, int x)
{
    list_ptr temp = stack->next;
    if(temp->next == NULL)
        return;
    int el = temp->el;
    if(el == 3){
        parantheses(stack, post);
        return;
    }
    else if(el == 2)
        return;

    while(temp->next != NULL){
        if(el <= temp->next->el && temp->next->el < 2)
            pop_to_postfix(post, stack, temp->next->op);
        else
            return;
        temp = temp->next;
    }
}
void parantheses(list_ptr stack, list_ptr post)
{
    list_ptr temp, stack_free;
    list_ptr head_free = stack->next;
    stack->next = stack->next->next;
    free(head_free);
    while(stack->next->el != 2){
        temp = (list_ptr)malloc(sizeof(list));
        temp->next = post->next;
        post->next = temp;
        temp->op = stack->next->op;
        temp->el = 0;

        stack_free = stack->next;
        stack->next = stack->next->next;
        free(stack_free);
    }
    stack_free = stack->next;
    stack->next = stack->next->next;
    free(stack_free);
}
void pop_to_postfix(list_ptr post, list_ptr stack, int x)
{
    list_ptr temp = malloc(sizeof(list));
    temp->op = x;
    temp->next = post->next;
    post->next = temp;
    list_ptr temp_free = stack->next;
    temp_free->next->op = temp_free->op;
    temp_free->next->el = temp_free->el;
    stack->next = temp_free->next;
    free(temp_free);
}
int print(list_ptr ptr)
{
    if(ptr->next == NULL)
        return 0;
    while(ptr->next != NULL){
        if(ptr->next->op != '\0')
            printf("%c ", ptr->next->op);
        else
            printf("%d ", ptr->next->el);
        ptr = ptr->next;
    }
    printf("\n");
    return 0;
}
int is_number(int x)
{
    return (x < 58 && x > 47) ? 1 : 0;
}
int is_operator(int c)
{
    return ((c < 48 && c > 39 && c != 44 && c != 46) || (c == 92)) ? 1 : 0;
}
void push_int(list_ptr ptr, int x, int *y)
{
    if(*y){
        ptr->next->el = (ptr->next->el * 10) + x;
    }
    else{
        list_ptr temp = malloc(sizeof(list));
        temp->next = ptr->next;
        ptr->next = temp;
        temp->el = x;
        temp->op = '\0';
    }
}
void push_char(list_ptr ptr, int x)
{
    list_ptr temp = malloc(sizeof(list));
    temp->next = ptr->next;
    ptr->next = temp;
    temp->op = x;
    if(x == 43 || x == 45)
        temp->el = 0;
    else if(x == 42 || x == 47)
        temp->el = 1;
    else if(x == 40)
        temp->el = 2;
    else if(x == 41)
        temp->el = 3;
    else
        printf("ERROR\n");
}
void pop(list_ptr ptr, int x)
{
    list_ptr temp, temp_free; 
    temp_free = ptr->next;
    temp = ptr->next->next;
    temp->el += temp_free->el;
    free(temp_free);
}  
void push_end(list_ptr post, list_ptr stack)
{
    list_ptr temp_free = NULL;
    while(stack->next != NULL){
        list_ptr temp = malloc(sizeof(list));
        temp->op = stack->next->op;
        temp->next = post->next;
        post->next = temp;
        stack = stack->next;
        if(temp_free != NULL)
            free(temp_free);
        temp_free = stack;
    }
}

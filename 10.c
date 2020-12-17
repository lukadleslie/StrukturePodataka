#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node *ptr;
typedef struct stack *stack_ptr;
typedef struct node{
    char operand, operator;
    ptr right, left;
}node;
typedef struct stack{
    ptr address;
    stack_ptr next;
}stack;

int create_infix(ptr);
int print_tree(ptr,int);
int read(char**);
void print(stack_ptr);
void push(ptr,stack_ptr);
ptr pop(ptr,stack_ptr);
ptr create_node(char,char);
ptr create_tree(char*);

int main(void)
{
    ptr root;

    char *dat = malloc(128);
    strcpy(dat, "datoteke/10.txt");

    if(!read(&dat))
        printf("File not found\n");

    root = create_tree(dat);
    print_tree(root, 0);
    create_infix(root);
    printf("\n");

    return 0;
}
ptr create_node(char oprand, char oprator)
{
    ptr cvor = malloc(sizeof(node));
    cvor->operand = oprand;
    cvor->operator = oprator;
    cvor->left = cvor->right = NULL;
    return cvor;
}
int read(char **input)
{
    char name[128];
    FILE *p = fopen(*input, "r");
    if(p == NULL)
        return 0;
    **input = '\0';
    fscanf(p, "%[^\n]", *input);
    fclose(p);
    return 1;
}
ptr create_tree(char *input)
{
    stack stog;
    stog.next = NULL;
    stack_ptr stog_ptr = &stog;
    ptr root;
    int i = 0;
    while(input[i++] != '\0')
        if(isalpha(input[i-1]) || isdigit(input[i-1]))
            push(create_node(input[i-1], '\0'), stog_ptr);
        else if(input[i-1] != ' ')
            root = pop(create_node('\0', input[i-1]), stog_ptr);
    return root;
}
void push(ptr node, stack_ptr stack)
{
    stack_ptr temp = malloc(sizeof(stack));
    temp->address = node;
    temp->next = stack->next;
    stack->next = temp;
}
ptr pop(ptr cvor, stack_ptr stack)
{
    int i = 0;
    stack_ptr stack_free;

    cvor->right = stack->next->address;
    cvor->left = stack->next->next->address;

    while(i++ != 2){
        stack_free = stack->next;
        stack->next = stack->next->next;
        free(stack_free);
    }
    stack_ptr temp = malloc(sizeof(stack));
    temp->address = cvor;
    temp->next = stack->next;
    stack->next = temp;

    return cvor;
}
void print(stack_ptr ptr)
{
    while(ptr->next != NULL){
        if(ptr->next->address->operand != '\0')
            printf("%c\n", ptr->next->address->operand);
        else
            printf("%c\n", ptr->next->address->operator);
        ptr = ptr->next; 
    }
}
int print_tree(ptr current, int space) 
{ 
    if(current == NULL) 
        return 0; 
    space += 10; 
    if (current->right != NULL)
        print_tree(current->right, space); 
    printf("\n"); 
    for (int i = 10; i < space; i++) 
        printf(" "); 
    if(current->operand != '\0')
        printf("%c\n", current->operand); 
    else
        printf("%c\n", current->operator); 
    if (current->left != NULL)
        print_tree(current->left, space); 
    return 1;
}
int create_infix(ptr current)
{
    if(current == NULL)
        return 1;
    if(current->left)
        create_infix(current->left);
    if(current->operand != '\0')
        printf("%c ", current->operand);
    else
        printf("%c ", current->operator);
    if(current->right)
        create_infix(current->right);
    return 0;
}

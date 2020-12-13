#include <stdio.h>
#include <stdlib.h>

#define M 10

typedef struct node *ptr;
typedef struct node{
    int el;
    ptr left;
    ptr right;
} node;

ptr create_node(int);
void add_node(ptr,int);
void print(ptr,int);
int is_number(char);
int input(void);
int find(ptr,int);
int delete(ptr,int);

int main()
{
    int x, i = 0;
    ptr head;

    printf("How many nodes would you like to insert: ");
    scanf("%d", &i);
    
    if(!i)
        return 0;

    printf("Enter head val: ");
    scanf("%d", &x);
    head = create_node(x);

    do{
        printf("enter val: "); 
        if((x = input()))
            add_node(head, x);
        else{
            printf("Please enter a valid integer...\n");
            ++i;
        }
    } while(--i);

    print(head, 0);

    printf("\n\n\n");
    return 0;
}
ptr create_node(int x)
{
    ptr temp = malloc(sizeof(node));
    temp->el = x;
    temp->right = temp->left = NULL;
    return temp;
}
void add_node(ptr head, int x)
{
    ptr new = create_node(x);
    ptr current = head;
    while(current != NULL){
        if(new->el >= current->el){
            if(current->right == NULL){
                current->right = new;
                break;
            }
        current = current->right;
        }
        else{
            if(current->left == NULL){
                current->left = new;
                break;
            }
            current = current->left;
        }
    }
}
void print(ptr current, int space) 
{ 
    if(current == NULL) 
        return; 
    space += M; 
    if (current->right != NULL)
        print(current->right, space); 
    printf("\n"); 
    for (int i = M; i < space; i++) 
        printf(" "); 
    printf("%d\n", current->el); 
    if (current->left != NULL)
        print(current->left, space); 
} 
int input()
{
    int x = 0, prev = 0;
    char *c = malloc(20);
    scanf(" %[^\n]", c);
    while(*c != '\n'){
        if((x = is_number(*c)) && prev){
            prev *= 10;
            prev += x;
        }
        else if(x)
            prev = x;
        else if(*c == '0')
            prev *= 10;
        else if(prev)
            return prev;
        else 
            return 0;
        c++;
    }
    return 0;
}
int is_number(char x)
{
    return (x < 58 && x > 47) ? (x-48) : 0;
}
int find(ptr current, int el)
{
    return 0;
}
int delete(ptr current, int el)
{
    return 0;
}

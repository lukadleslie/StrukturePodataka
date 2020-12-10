#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 64

typedef struct directory *ptr;
typedef struct directory{
    char name[M];
    ptr child;
    ptr next;
} directory;

typedef struct stack *stack_ptr;
typedef struct stack{
    char* name;
    ptr next;
} stack;

int unos(char*);
int mkdir(ptr, char*);
int mkchild(ptr, char*);
int change_dir(ptr, char*);
int exists(ptr, char*);
int empty_dir(ptr);
int print(ptr);

int main()
{
    directory dir; dir.next = NULL; dir.child = NULL; strcpy(dir.name, "~");
    stack stack; stack.next = NULL;
    char c[M], ime[M];
    int d = 1, i = 0, empty;

    do{
        printf("\n%s ", dir.name);

        if(unos(c)){
            unos(ime);
            empty = 0;
        }
        else{
            ime[0] = '\0';
            empty = 1;
        }

        if(!strcmp(c, "mkdir")){
            if(empty)
                printf("\nDirectory must have a name\n");
            else if (empty_dir(&dir))
                mkchild(&dir, ime);
            else if(exists(&dir, ime))
                printf("\nA directory with that name already exists in current directory\n");
            else
                mkdir(&dir, ime);
        }
        else if(!strcmp(c, "ls")){
            if(empty_dir(&dir))
                printf("\nempty...\n");
            else
                print(&dir);
        }
        else if((!strcmp(c, "cd")) && (!empty)){
            if(!exists(&dir, ime))
                printf("\nNo such file or directory\n");
            else{
                //push to stack function here//
                change_dir(&dir, ime);
            }
        } 
        else if((!strcmp(c, "cd")) && empty){
            //pop from stack function here//
        }
        else if((!strcmp(c, "clear")) || (!strcmp(c, "c"))){
            system("clear");
        }
        else if(!strcmp(c, "q"))
            d = 0;
        else
            printf("command not found\n");
    } while(d);

    return 0;
}
int unos(char* string)
{
    char c; int i = 0;
    while((c = fgetc(stdin)) != '\n' && c != ' '){
        string[i] = c;
        i++;
    }
    string[i] = '\0';
    if(c == '\n')
        i = 0;
    return i;
}
int mkchild(ptr dir, char* ime)
{
    ptr kid = malloc(sizeof(directory));
    strcpy(kid->name, ime);
    kid->next = NULL;
    kid->child = NULL;
    dir->child = kid;
    return 0;
}
int mkdir(ptr root, char* ime)
{
    root = root->child;
    ptr dir = malloc(sizeof(directory));
    strcpy(dir->name, ime);
    dir->next = root->next;
    root->next = dir;
    dir->child = NULL;
    return 0;
}
int change_dir(ptr dir, char* ime)
{
    ptr temp = dir;
    printf("%s\n", temp->child->name);
    printf("%s\n", temp->child->next->name);
    while(strcmp(temp->name, ime)){
        printf("%s  %s\n", temp-name, ime);
        temp = temp->next;
    }
    dir = temp;
    return 0;
}
int print(ptr p)
{
    ptr dir = p->child; 
    while(dir != NULL){
        printf("\n%s\n", dir->name);
        dir = dir->next;
    }
    return 0;
}
int exists(ptr ptr, char* ime)
{
    ptr = ptr->child;
    while(ptr != NULL){
        if(!strcmp(ptr->name, ime))
            return 1;
        ptr = ptr->next;
    }
    return 0;
}
int empty_dir(ptr ptr)
{
    if(ptr->child == NULL)
        return 1;
    return 0;
}

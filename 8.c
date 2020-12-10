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
int change_dir(ptr, char*);
int exists(ptr, char*);
int empty_dir(ptr);
int print(ptr);

int main()
{
    directory dir, root; dir.next = NULL, root.next = NULL;
    stack stack; stack.next = NULL;
    char c[M], ime[M];
    int d = 1, i = 0, empty;

    do{
        if(0)
            printf("\n%s ", dir.name);
        else
            printf("\n~  ");
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
            else if(exists(&dir, ime))
                printf("\nA directory with that name already exists in current directory\n");
            else{
                mkdir(&dir, ime);
                print(&dir);
            }
        }
        else if(!strcmp(c, "ls")){
            if(empty_dir(&dir))
                ;
            else
                print(&dir);
        }
        else if(!strcmp(c, "cd")){
            if(!exists(&dir, ime))
                printf("No such file or directory\n");
            else{
                change_dir(&dir, ime);
                print(&dir);
                //push to stack function here//
            }
        } 
        else if(!strcmp(c, "cd-")){
            //pop from stack function here//
        }
        else if((!strcmp(c, "clear")) || (!strcmp(c, "c"))){
            system("clear");
        }
        else if(!strcmp(c, "q"))
            d = 0;
        else{
            printf("command not found\n");
        }
    }while(d);

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
int mkdir(ptr root, char* ime)
{
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
    while(strcmp(temp->next->name, ime))
        temp = temp->next;
    dir = temp->next;
    return 0;
}
int print(ptr ptr)
{
    while(ptr->next != NULL){
        printf("\n%s\n", ptr->next->name);
        ptr = ptr->next;
    }
    return 0;
}
int exists(ptr ptr, char* ime)
{
    while(ptr->next != NULL){
        if(!strcmp(ptr->next->name, ime))
            return 1;
        ptr = ptr->next;
    }
    return 0;
}
int empty_dir(ptr ptr)
{
    if(ptr->next == NULL){
        printf("\nempty...\n");
        return 1;
    }
    return 0;
}

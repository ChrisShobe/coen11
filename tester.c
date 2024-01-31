#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//global variables
union u
{
    int bday[2];
    char ophone[20];
};

struct node
{
    char number[10];
    char fname[10];
    char lname[10];
    int flag;
    union u otherInfo;
    struct node *next;
};



struct node *head = NULL;

//function prototypes
void insert();
void show_all();
void show_name();
void delete();
void delete_name();

int main(void)
{
    int option;
    while(1)
    {
        printf("Please enter option (1 for insert, 2 for list, 3 to find name, 4 to delete indiviual, 5 to delete all of specific name, 0 to quit): \n");
        if (scanf (" %d", &option) != 1)
        {
            printf ("error\n");
            return 0;
        }
        
        switch(option)
        {
            case 1:
                insert();
                break;
            
            case 2:
                show_all();
                break;
            
            case 3:
                show_name();
                break;
                
            case 4:
                delete();
                break;
                
            case 5:
                delete_name();
                break;
            
            case 0:
                return 0;
            
            default:
                printf ("wrong option\n");
                break;
        }
    }
}

int check_duplicate(char fn[], char ln[])
{
    printf("check_duplicate\n");
    struct node *p = head;
    int i;
    while(p->next != NULL) 
    {
        printf("while\n");
        if(strcmp(fn, p->fname) == 0 && strcmp(ln, p->lname) == 0)
        {
            printf("is 1\n");
            return 1;
        }
        p = p->next;
    }
    printf("is 0\n");
    return 0;
}

void order(char fn[], char ln[], char num[], int f, int bd[], char op[])
{
    printf("order\n");
    struct node *p = head;
    int place = -1;
    int i;
    while(p->next != NULL) 
    {
        if(strcmp (ln, p->next->lname) == 0)
        {
            if(strcmp(fn, p->next->fname) < 0)
            {
                place = i;
                break;
            }
            else
            {
                place = i + 1;
                break;
            }
        }
        else if(strcmp (ln, p->next->lname) < 0) //less than the thing
        {
            place = i;
            break;
        }
        p = p->next;
    }
    
    if(place != -1)
    {
        int j;
        struct node *temp = p->next;
        strcpy(p->next->lname, ln);
        strcpy(p->next->fname, fn);
        strcpy(p->next->number, num);
        p->next->flag = f;
        p->next->next = temp;
        
        if(f == 0)
        {
            p->next->otherInfo.bday[0] = bd[0];
            p->next->otherInfo.bday[1] = bd[1];
        }
        if(f == 1)
        {
            /*printf("got in f == 1\n");
            printf("op is %s", op);*/
            strcpy(p->otherInfo.ophone, op);
            /*printf("ophone is ");
            printf("%s\n", people[place].otherInfo.ophone);*/
        }
    }
    else
    {
        strcpy(p->next->lname, ln);
        strcpy(p->next->fname, fn);
        strcpy(p->next->number, num);
        p->next->flag = f;
        p->next->next = NULL;
        if(f == 0)
        {
            p->next->otherInfo.bday[0] = bd[0];
            p->next->otherInfo.bday[1] = bd[1];
        }
        if(f == 1)
        {
            /*printf("got in f == 1\n");
            printf("op is %s", op);*/
            strcpy(p->otherInfo.ophone, op);
            /*printf("ophone is ");
            fputs(people[counter].otherInfo.ophone, stdout);*/
        }    
    }
    
}

void insert()
{
    struct node *p = malloc(sizeof(head));
    printf("Enter the first name: \n");
    scanf(" %s", p->fname); //gets name
    fflush(stdin);
    printf("Enter the last name: \n");
    scanf(" %s", p->lname); //gets name
    fflush(stdin);
    int r = check_duplicate(p->fname, p->lname);
    //printf("r: %i\n", r);
    if (r == 1)
    {
        printf("Repeated name. Try again. \n");
        return;
    }
    else
    {
        printf("Enter the phone number: \n");
        scanf(" %[^\n]*c", p->number); //gets number
        printf("Enter flag number (0 for birthday, 1 for ophone, 2 for N/A): \n");
        scanf(" %i", &p->flag); 
        if(p->flag == 0)
        {
            printf("Enter your birthday day: \n");
            scanf(" %d", &(p->otherInfo.bday[0]));
            scanf(" %d", &(p->otherInfo.bday[1]));
        }
        else if(p->flag == 1)
        {
            printf("Enter other phone number: \n");
            scanf("%s", p->otherInfo.ophone);
            //printf("op is %s", op); // checking stored
        }
        else if(p->flag == 2)
        {
            printf("No other info.\n");
        }
        else
        {
            printf("error\n");
        }
        order(p->fname, p->lname, p->number, p->flag, p->otherInfo.bday, p->otherInfo.ophone);
    }
    
}

void delete()
{
    struct node *p = head;
    struct node *temp = malloc(sizeof(head));
    printf("Enter first name to delete: \n");
    scanf(" %s", temp->fname);
    printf("Enter last name to delete: \n");
    scanf(" %s", temp->lname);
    while(p->next != NULL)
    {
        if(strcmp(temp->fname, p->next->fname) == 0 && strcmp(temp->fname, p->next->lname) == 0)
        {
            temp = p->next;
            p->next = p->next->next;
            free(temp);
            break;
        }
        p = p->next;
    }
}
void delete_name()
{
    struct node *p = head;
    struct node *temp = malloc(sizeof(head));
    printf("Enter first name to delete: \n");
    scanf(" %s", temp->fname);
    while(p->next != NULL)
    {
        if(strcmp(temp->fname, p->fname) == 0)
        {
            temp = p->next;
            p->next = p->next->next;
            free(temp);
        }
        p = p->next;
    }
}

void show_all()
{
    struct node *person = head;
    while(person->next != NULL) // finds all names in list
    {
        printf("First Name: ");
        fputs(person->fname, stdout);
        printf(" Last Name: ");
        fputs(person->lname, stdout);
        printf(" Phone Number: ");
        fputs(person->number, stdout);
        if(person->flag == 0)
        {
            printf(" Birthday: ");
            printf("%d", person->otherInfo.bday[0]);
            printf("/%d\n", person->otherInfo.bday[1]);
        }
        else if(person->flag == 1)
        {
            printf(" Other Phone Number: ");
            fputs(person->otherInfo.ophone, stdout);
            printf("\n");
        }
        else if(person->flag == 2)
        {
            printf(" There is no other info.\n");
        }
        person = person->next;
    }
}

void show_name()
{
    struct node *person = head;
    int current = 0;
    char findName[10];
    bool found = false;
    
    printf("Enter last name to find all people with the same last name: \n");
    scanf(" %[^\n]*c", findName);
    
    while(person->next != NULL)
    {
        if(strcmp(findName, person->lname) == 0)
        {
            printf("The number associated with %s, %s", person->fname, person->lname);
            printf(" is ");
            puts(person->number);
            found = true;
        }
        person = person->next;
    }
    if(found != true)
    {
        printf("The name inserted was not found.\n");
    }
}










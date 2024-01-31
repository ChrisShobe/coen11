#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//global variables

union u
{
    int bday[2];
    char ophone[20];
};

struct info
{
    char number[10];
    char fname[10];
    char lname[10];
    int flag;
    union u otherInfo;
};

struct info people[20];
int counter = 0;

    
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
    int i;
    for(i = 0; i < counter; i++) 
    {
        if(strcmp(fn, people[i].fname) == 0 && strcmp(ln, people[i].lname) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void order(char fn[], char ln[], char num[], int f, int bd[], char op[])
{
    //if counter == 1 exit
    //printf(" f is %d\n", f);
    int place = -1;
    int i;
    for(i = 0; i < counter; i++)
    {
        if(strcmp (ln, people[i].lname) == 0)
        {
            if(strcmp(fn, people[i].fname) < 0)
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
        else if(strcmp (ln, people[i].lname) < 0) //less than the thing
        {
            place = i;
            break;
        }
    }
    
    if(place != -1)
    {
        int j;
        for(j = counter; j >= place; j--)
        {
            //printf("changing %s to %s", fname[j+1], fname[j]);
            people[j+1] = people[j];
        }
        strcpy(people[place].lname, ln);
        strcpy(people[place].fname, fn);
        strcpy(people[place].number, num);
        if(f == 0)
        {
            people[place].otherInfo.bday[0] = bd[0];
            people[place].otherInfo.bday[1] = bd[1];
        }
        if(f == 1)
        {
            /*printf("got in f == 1\n");
            printf("op is %s", op);*/
            strcpy(people[place].otherInfo.ophone, op);
            /*printf("ophone is ");
            printf("%s\n", people[place].otherInfo.ophone);*/
        }
    }
    else
    {
        strcpy(people[counter].lname, ln);
        strcpy(people[counter].fname, fn);
        strcpy(people[counter].number, num);
        if(f == 0)
        {
            people[counter].otherInfo.bday[0] = bd[0];
            people[counter].otherInfo.bday[1] = bd[1];
        }
        if(f == 1)
        {
            /*printf("got in f == 1\n");
            printf("op is %s", op);*/
            strcpy(people[counter].otherInfo.ophone, op);
            /*printf("ophone is ");
            fputs(people[counter].otherInfo.ophone, stdout);*/
        }    
    }
    
}

void insert()
{
    char fn[10];
    char ln[10];
    char num[10];
    struct info compare[20];
    int f;
    int bd[2];
    char op[20];
    printf("Enter the first name: \n");
    scanf(" %s", fn); //gets name
    fflush(stdin);
    printf("Enter the last name: \n");
    scanf(" %s", ln); //gets name
    fflush(stdin);
    int r = check_duplicate(fn, ln);
    /*printf("r: ");
    printf(" %i", r);*/
    if (r == 1)
    {
        printf("Repeated name. Try again. \n");
        return;
    }
    else
    {
        printf("Enter the phone number: \n");
        scanf(" %[^\n]*c", num); //gets number
        printf("Enter flag number (0 for birthday, 1 for ophone, 2 for N/A): \n");
        scanf(" %i", &f); 
        if(f == 0)
        {
            printf("Enter your birthday day: \n");
            scanf(" %d", &(bd[0]));
            scanf(" %d", &(bd[1]));
        }
        else if(f == 1)
        {
            printf("Enter other phone number: \n");
            scanf("%s", op);
            //printf("op is %s", op); // checking stored
        }
        else if(f == 2)
        {
            printf("No other info.\n");
        }
        else
        {
            printf("error\n");
        }
        people[counter].flag = f;
        order(fn, ln, num, f, bd, op);
    }
    
    counter++;
}

void delete()
{
    char fn[10];
    char ln[10];
    printf("Enter first name to delete: \n");
    scanf(" %s", fn);
    printf("Enter last name to delete: \n");
    scanf(" %s", ln);
    int i;
    for(i = 0; i < counter; i++)
    {
        if(strcmp(fn, people[i].fname) == 0 && strcmp(ln, people[i].lname) == 0)
        {
            int j;
            for(j = i; j < counter - 1; j++)
            {
                people[j] = people[j+1]; 
            }
            break;
        }
    }
    counter--;
}

void delete_name()
{
    char fn[10];
    printf("Enter first name to delete: \n");
    scanf(" %s", fn);
    int i;
    for(i = 0; i < counter; i++)
    {
        if(strcmp(fn, people[i].fname) == 0)
        {
            int j;
            for(j = i; j < counter - 1; j++)
            {
                people[j] = people[j+1];
            }
            counter--;
        }
    }
}

void show_all()
{
    struct info *person = &people[0];
    int current = 0;
    for(; current < counter; current++, person++) // finds all names in list
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
    }
}

void show_name()
{
    struct info *person = &people[0];
    int current = 0;
    char findName[10];
    bool found = false;
    
    printf("Enter last name to find all people with the same last name: \n");
    scanf(" %[^\n]*c", findName);
    
    for(current = 0; current < counter; current++, person++)
    {
        if(strcmp(findName, person->lname) == 0)
        {
            printf("The number associated with ");
            fputs(findName, stdout);
            printf(" is ");
            puts(person->number);
            found = true;
        }
        
    }
    if(found != true)
    {
        printf("The name inserted was not found.\n");
    }
}





#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//global variables

struct info
{
    char number[10];
    char fname[10];
    char lname[10];
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

void order(char fn[], char ln[], char num[])
{
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
            strcpy(people[j+1].lname, people[j].lname);
            strcpy(people[j+1].fname, people[j].fname);
            strcpy(people[j+1].number, people[j].number);
        }
        strcpy(people[place].lname, ln);
        strcpy(people[place].fname, fn);
        strcpy(people[place].number, num);
        
    }
    else
    {
        strcpy(people[counter].lname, ln);
        strcpy(people[counter].fname, fn);
        strcpy(people[counter].number, num);
    }
    
}

void insert()
{
    char fn[10];
    char ln[10];
    char num[10];
    struct info compare[20];
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
        if(counter == 0)
        {
            strcpy(people[0].fname, fn);
            strcpy(people[0].lname, ln);
            printf("Enter the phone number: \n");
            scanf(" %[^\n]*c", people[0].number); //gets number
        }
        else
        {
            printf("Enter the phone number: \n");
            scanf(" %[^\n]*c", num); //gets number
            order(fn, ln, num);
        }
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
                strcpy(people[j].fname, people[j+1].fname);
                strcpy(people[j].lname, people[j+1].lname);
                strcpy(people[j].number, people[j+1].number);
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
    int i, j;
    for(i = 0; i < counter; i++)
    {
        if(strcmp(fn, people[i].fname) == 0)
        {
            for(j = i; j < counter - 1; j++)
            {
                strcpy(people[j].fname, people[j+1].fname);
                strcpy(people[j].lname, people[j+1].lname);
                strcpy(people[j].number, people[j+1].number);
            }
            counter--;
        }
    }
}

void show_all()
{
    struct info *person = &people[0];
    int current = 0;
    for(current = 0; current < counter; current++, person++) // finds all names in list
    {
        printf("First Name: ");
        fputs(person->fname, stdout);
        printf(" Last Name: ");
        fputs(person->lname, stdout);
        printf(" Phone Number: ");
        puts(person->number);
    }
}

void show_name()
{
    struct info *person = &people[0];
    int current = 0;
    char findName[10];
    bool found = false;
    
    printf("Enter name to find number: \n");
    scanf(" %[^\n]*c", findName);
    
    for(current = 0; current < counter; current++, person++)
    {
        if(strcmp(findName, person->fname) == 0)
        {
            printf("The number associated with ");
            fputs(findName, stdout);
            printf(" is ");
            puts(person->number);
            found = true;
            break;
        }
        
    }
    if(found != true)
    {
        printf("The name inserted was not found.\n");
    }
}












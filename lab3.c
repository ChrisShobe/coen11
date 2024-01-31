
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//global variables
char number[10][10];
char fname[10][10];
int counter = 0;

//function prototypes
void insert();
void show_all();
void show_name();
void delete();

int main(void)
{
    int option;
    while(1)
    {
        printf("Please enter option (1 for insert, 2 for list, 3 to find name, 4 to delete name, 0 to quit: \n");
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
            
            case 0:
                return 0;
            
            default:
                printf ("wrong option\n");
                break;
        }
    }
}

int check_duplicate(char n[])
{
    //printf("executed \n");
    int i;
    for(i = 0; i < 10; i++) // would not execute if put < counter even though executed in other functions
    {
        /*printf("fname: ");
        printf(" %s", fname[i]);
        printf("\n");
        
        printf("n: ");
        printf(" %s", n);
        printf("\n");*/
        if(strcmp(n, fname[i]) == 0)
        {
            //printf("=1");
            return 1;
        }
    }
    //printf("=0");
    return 0;
}

void order(char n[], char num[])
{
    int place = -1;
    int i;
    for(i = 0; i < counter; i++)
    {
        if(strcmp (n, fname[i]) < 0) //less than the thing
        {
            place = i;
            //printf("num is set to %i", num);
        }
    }
    
    if(place != -1)
    {
	int j;
        for(j = counter; j >= place; j--)
        {
            //printf("changing %s to %s", fname[j+1], fname[j]);
            strcpy(fname[j+1], fname[j]);
            strcpy(number[j+1], number[j]);
        }
        strcpy(fname[place], n);
        strcpy(number[place], num);
        
    }
    else
    {
        strcpy(fname[counter], n);
        strcpy(number[counter], num);
    }
    
}

void insert()
{
    char name[10];
    char num[10];
    printf("Enter the first name: \n");
    scanf(" %s", name); //gets name
    fflush(stdin);
    int r = check_duplicate(name);
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
            strcpy(fname[0], name);
            printf("Enter the phone number: \n");
            scanf(" %[^\n]*c", number[0]); //gets number
        }
        else
        {
            printf("Enter the phone number: \n");
            scanf(" %[^\n]*c", num); //gets number
            order(name, num);
        }
    }
    
    counter++;
}

void delete()
{
    char n[10];
    printf("Enter name to delete: \n");
    scanf(" %s", n);
    int i;
    for(i = 0; i < 10; i++)
    {
        if(strcmp(n, fname[i]) == 0)
        {
	int j;
            for(j = i; j < 9; j++)
            {
                strcpy(fname[j], fname[j+1]);
                strcpy(number[j], number[j+1]);
            }
            break;
        }
    }
    counter--;
}

void show_all()
{
    int i;
    for(i = 0; i < counter; i++) // finds all names in list
    {
        printf("First Name: ");
        fputs(fname[i], stdout);
        printf(" Phone Number: ");
        puts(number[i]);
    }
}

void show_name()
{
    char findName[10];
    bool found = false;
    
    printf("Enter name to find number: \n");
    scanf(" %[^\n]*c", findName);
    
    int i;
    for(i = 0; i < counter; i++)
    {
        if(strcmp(findName, fname[i]) == 0)
        {
            printf("The number associated with ");
            fputs(findName, stdout);
            printf(" is ");
            puts(number[i]);
            found = true;
            break;
        }
        
    }
    if(found != true)
    {
        printf("The name inserted was not found.\n");
    }
}







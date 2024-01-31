/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
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

int main(void)
{
    int option;
    while(1)
    {
        printf("Please enter option (1 for insert, 2 for list, 3 to find name, 0 to quit: \n");
        //scanf(" %c", &option);
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
            
            case 0:
                return 0;
            
            default:
                printf ("wrong option\n");
                break;
        }
    }
}

void insert()
{
    printf("Enter the first name: \n");
    scanf(" %[^\n]*c", fname[counter]); //gets name
    fflush(stdin);
    printf("Enter the phone number: \n");
    scanf(" %[^\n]*c", number[counter]); //gets number
    
    counter++;
}

void show_all()
{
    int column = 0;
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










#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

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

extern struct node *head;

//function prototypes
void insert();
void show_all();
void show_name();
void delete();
void delete_name();

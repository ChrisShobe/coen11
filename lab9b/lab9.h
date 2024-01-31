#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

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

extern struct node *heads[3];
extern pthread_mutex_t mutex;

//function prototypes
void read_from_keyboard();
void show_all();
void show_name();
void delete();
void delete_name();
void read_from_file(char* filename);
void save_to_file(char* filename);
void delete_all();
void binary_read_from_file(char* filename);
void* binary_save_to_file(void* filename);
#include "lab10.h"

struct node *heads[3];
pthread_mutex_t mutex;


int main (int argc, char *argv[])
{
    if(argc < 4)
    {
        printf("missing arguments\n");
        return 1;
    }
    pthread_t thread;    
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&thread, NULL, binary_save_to_file, (void *)argv[2]);
    int option;
    int key = atoi(argv[3]);
    read_from_file(argv[1], key);
    while(1)
    {
        printf("Please enter option (1 for insert, 2 for list, 3 to find name, 4 to delete indiviual, 5 to delete all of specific name, 6 to show the binary file, 0 to quit): \n");
        if (scanf (" %d", &option) != 1)
        {
            printf ("error\n");
            return 0;
        }
        
        switch(option)
        {
            case 1:
	            read_from_keyboard();//call keyboard
                break;
            
            case 2:
                show_all();
                break;
            
            case 3:
                show_name();
                break;
                
            case 4:
                pthread_mutex_lock(&mutex);
                delete();
                pthread_mutex_unlock(&mutex);
                break;
                
            case 5:
                pthread_mutex_lock(&mutex);
                delete_name();
                pthread_mutex_unlock(&mutex);
                break;
            case 6:
                pthread_mutex_lock(&mutex);
                binary_read_from_file(argv[2]);
                pthread_mutex_unlock(&mutex);
                break;

            case 0:
                save_to_file(argv[1], key);
                delete_all(heads[0], 0); 
                pthread_mutex_lock(&mutex);
                pthread_cancel(thread);
                pthread_mutex_unlock(&mutex);
                return 0;
            
            default:
                printf ("wrong option\n");
                break;
        }
    }
}

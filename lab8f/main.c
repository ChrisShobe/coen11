#include "lab8.h"

struct node *heads[3];

int main (int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("The name of the file is missing!\n");
        return 1;
    }
    int option;
    read_from_file(argv[1]);
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
	        read_from_keyboard();//call keyboard
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
	        save_to_file(argv[1]);
            delete_all(heads[0], 0);
	        return 0;
            
            default:
                printf ("wrong option\n");
                break;
        }
    }
}

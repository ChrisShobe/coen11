#include "lab9.h"
void binary_read_from_file(char* filename)
{
    //read nodes and show the contents on the screen
    struct node *temp = malloc(sizeof(struct node));
	FILE *file = fopen(filename, "rb");
	if(file == NULL)
	{
		perror("File opening failed");
		return;
	}
	while(fread(temp, sizeof(struct node), 1, file) > 0)
	{
        printf("First Name: %s", temp->fname);
        printf(" Last Name: %s", temp->lname);
        printf(" Phone Number: %s", temp->number);
        if(temp->flag == 0)
        {
            printf(" Birthday: ");
            printf("%d", temp->otherInfo.bday[0]);
            printf("/%d\n", temp->otherInfo.bday[1]);
        }
        else if(temp->flag == 1)
        {
            printf(" Other Phone Number: ");
            fputs(temp->otherInfo.ophone, stdout);
            printf("\n");
        }
        else if(temp->flag == 2)
        {
            printf(" There is no other info.\n");
        }
		temp = malloc(sizeof(struct node));
	}
	fclose(file);
}

void* binary_save_to_file(void* filename)
{
    while(1)
    {
        sleep(15);
        FILE *file = fopen((char*)filename, "wb");
        if(file == NULL)
        {
            perror("File opening failed");
            return;
        }
        int i;
        pthread_mutex_lock(&mutex);
        for(i = 0; i < 3; i++)
        {
            struct node *current = heads[i];
            while(current != NULL)
            {
                fwrite(current, sizeof(struct node), 1, file);
                current = current -> next;
                printf("debug\n");
            }
        }
        pthread_mutex_unlock(&mutex);                
        printf("saved\n");
        fclose(file);
    }
}
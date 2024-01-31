#include "lab9.h"

void read_from_file(char* filename)
{
	struct node *temp = malloc(sizeof(struct node));
	FILE *file = fopen(filename, "r");
	if(file == NULL)
	{
		perror("File opening failed");
		return;
	}
	while(fscanf(file, "%s %s %s %d", temp->fname, temp->lname, temp->number, &temp->flag) == 4)
	{
		if(temp->flag == 0)
		{
		  fscanf(file, "\t %d", &(temp->otherInfo.bday[0]));
		  fscanf(file, " %d", &(temp->otherInfo.bday[1]));
		}
		else if(temp->flag == 1)
		{
		  fscanf(file, "\t %s", temp->otherInfo.ophone);
		    //printf("op is %s", op); // checking stored
		}
		else if(temp->flag == 2){}
		else
		{
		    printf("error\n");
		}
		
		pthread_mutex_lock(&mutex);
		insert(temp);
        pthread_mutex_unlock(&mutex);		
		temp = malloc(sizeof(struct node));
	}
	fclose(file);
}

void save_to_file(char* filename)
{
	FILE *file = fopen(filename, "w");
	if(file == NULL)
	{
		perror("File opening failed");
		return;
	}
	int i;
	for(i = 0; i < 3; i++)
	{
		struct node *current = heads[i];
		while(current != NULL)
		{
			if(current->flag == 0)
			{
			fprintf(file, "%s %s %s %d\t %d %d\n", current->fname, current->lname, current->number, current->flag, current->otherInfo.bday[0], current->otherInfo.bday[1]);
			}
			else if(current->flag == 1)
			{
			fprintf(file, "%s %s %s %d\t %s\n", current->fname, current->lname, current->number, current->flag, current->otherInfo.ophone);
			}
			else if(current->flag == 2)
			{
			fprintf(file, "%s %s %s %d\n", current->fname, current->lname, current->number, current->flag);
			}
			current = current->next;
		}
	}
	fclose(file);
}

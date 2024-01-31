#include "lab10.h"

void read_from_file(char* filename, int key)
{
	struct node *temp = malloc(sizeof(struct node));
	FILE *file = fopen(filename, "r");
	if(file == NULL)
	{
		perror("File opening failed");
		return;
	}
	char x[255];
	int k = 0;
	while(fgets(x, 254, file))
	{
		//decrypt
		while(x[k] != '\n')
		{
			x[k] = x[k] ^ key;
			k++;
		}
		//strtok for all variables
		if(strlen(x) == 1) break;
		strcpy(temp->fname, strtok(x, " "));
		strcpy(temp->lname, strtok(NULL, " "));
		strcpy(temp->number, strtok(NULL, " "));
		temp->flag = atoi(strtok(NULL, " "));
		if(temp->flag == 0)
		{
		 temp->otherInfo.bday[0] = atoi(strtok(NULL, " "));
		 temp->otherInfo.bday[1] = atoi(strtok(NULL, " "));
		}
		else if(temp->flag == 1)
		{
		  strcpy(temp->otherInfo.ophone, strtok(NULL, " "));
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

void save_to_file(char* filename, int key)
{
	FILE *file = fopen(filename, "w");
	if(file == NULL)
	{
		perror("File opening failed");
		return;
	}

	int i, k;
	char x[255];
	for(i = 0; i < 3; i++)
	{
		struct node *current = heads[i];
		while(current != NULL)
		{
			if(current->flag == 0)
			{
				sprintf(x, "%s %s %s %d %d %d \n", current->fname, current->lname, current->number, current->flag, current->otherInfo.bday[0], current->otherInfo.bday[1]);
			}
			else if(current->flag == 1)
			{
				sprintf(x, "%s %s %s %d %s \n", current->fname, current->lname, current->number, current->flag, current->otherInfo.ophone);
			}
			else if(current->flag == 2)
			{
				sprintf(x, "%s %s %s %d \n", current->fname, current->lname, current->number, current->flag);
			}
			k = 0;
			while(x[k] != '\n')
			{
				x[k] = x[k] ^ key;
				k++;
			}
			fprintf(file, "%s", x);
			fprintf(file, "\n");
			current = current->next;
		}
	}
	fclose(file);
}

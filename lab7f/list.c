#include "lab7.h"

int check_duplicate(char fn[], char ln[])
{
    //printf("check_duplicate\n");
    struct node *p = malloc(sizeof(struct node));
    if(head == NULL)
    {
        return 0;
    }
    else
    {
        p = head;
        while(p != NULL) 
        {
            /*printf("%s\n", fn);
            printf("%s\n",ln);
            printf("%s\n",head->fname);
            printf("%s\n",p->fname);
            printf("%s\n",p->lname);*/
            if(strcmp(fn, p->fname) == 0 && strcmp(ln, p->lname) == 0)
            {
                //printf("is 1\n");
                return 1;
            }
            p = p->next;
        }
    }
    //printf("is 0\n");
    return 0;
}

void insert(struct node *temp) 
{
    int r = check_duplicate(temp->fname, temp->lname);
    //printf("r: %i\n", r);
    if (r == 1)
    {
        printf("Repeated name. Try again. \n");
        return;
    }
    struct node *p = head;
    struct node *before = p;
    if(head == NULL) //nothing in list
    {
        head = temp;
        head->next = NULL;
        return;
    }
    
    if(strcmp(temp->lname, head->lname) == 0) //same last name as head
    {
        if(strcmp(temp->fname, p->fname) < 0)
        {
            temp->next = head;
            head = temp;
            return;
        }
        else
        {
            temp->next = head->next;
            head->next = temp;
            return;
        }
    }
    else if(strcmp(temp->lname, head->lname) < 0) // smaller last name to head
    {
        temp->next = head;
        head = temp;
        return;
    }
    
    else //greater than head   
    {
        while(p != NULL) 
        {
            if(strcmp(temp->lname, p->lname) == 0)
            {
                if(strcmp(temp->fname, p->fname) < 0)
                {
                    temp->next = before->next;
                    before->next = temp;
                    return;
                }
                else
                {
                    temp->next = p->next;
                    p->next = temp;
                    return;
                }
            }
            else if(strcmp(temp->lname, p->lname) < 0)
            {
                temp->next = before->next;
                before->next = temp;
                return;
            }
            before = p;
            p = p->next;
        }
    }
    
    if(p == NULL) //at end
    {
        before->next = temp;
        temp->next = NULL;
    }
    
}

void read_from_keyboard() //insert keyboard
{
    struct node *p = malloc(sizeof(struct node));
    printf("Enter the first name: \n");
    scanf(" %s", p->fname); //gets name
    fflush(stdin);
    printf("Enter the last name: \n");
    scanf(" %s", p->lname); //gets name
    fflush(stdin);
    printf("Enter the phone number: \n");
    scanf(" %[^\n]*c", p->number); //gets number
    printf("Enter flag number (0 for birthday, 1 for ophone, 2 for N/A): \n");
    scanf(" %i", &p->flag); 
    if(p->flag == 0)
    {
        printf("Enter your birthday day: \n");
        scanf(" %d", &(p->otherInfo.bday[0]));
        scanf(" %d", &(p->otherInfo.bday[1]));
    }
    else if(p->flag == 1)
    {
        printf("Enter other phone number: \n");
        scanf("%s", p->otherInfo.ophone);
        //printf("op is %s", op); // checking stored
    }
    else if(p->flag == 2)
    {
        printf("No other info.\n");
    }
    else
    {
        printf("error\n");
    }
    insert(p);
}

void delete()
{
    struct node *p = head;
    struct node *temp = malloc(sizeof(head));
    struct node *prev = head;
    printf("Enter first name to delete: \n");
    scanf(" %s", temp->fname);
    printf("Enter last name to delete: \n");
    scanf(" %s", temp->lname);
    
    
    while(p != NULL)
    {
        if(strcmp(temp->fname, p->fname) == 0 && strcmp(temp->lname, p->lname) == 0)
        {
            if(p == head)
            {
                head = head->next;
                free(p);
                return;
            }
            prev->next = p->next; // prev->next is p so skipping over
            free(p);
            return;
        }
        prev = p;
        p = p->next;
    }
}
void delete_name()
{
    struct node *p = head;
    struct node *temp = malloc(sizeof(struct node));
    struct node *prev = head;
    printf("Enter first name to delete: \n");
    scanf(" %s", temp->fname);
    while(p != NULL)
    {
        if(strcmp(temp->fname, p->fname) == 0)
        {
            if(p == head)
            {
                head = head->next;
                free(p);
            }
            else
            {
                prev->next = p->next; // prev->next is p so skipping over
                free(p);
            }
        }
        prev = p;
        p = p->next;
    }
}

void show_all()
{
    struct node *person = head;
    if(head == NULL)
    {
        return;
    }
    while(person != NULL) // finds all names in list
    {
        printf("First Name: %s", person->fname);
        printf(" Last Name: %s", person->lname);
        printf(" Phone Number: %s", person->number);
        if(person->flag == 0)
        {
            printf(" Birthday: ");
            printf("%d", person->otherInfo.bday[0]);
            printf("/%d\n", person->otherInfo.bday[1]);
        }
        else if(person->flag == 1)
        {
            printf(" Other Phone Number: ");
            fputs(person->otherInfo.ophone, stdout);
            printf("\n");
        }
        else if(person->flag == 2)
        {
            printf(" There is no other info.\n");
        }
        person = person->next;
    }
}

void show_name()
{
    struct node *person = head;
    char findName[10];
    bool found = false;
    
    printf("Enter last name to find all people with the same last name: \n");
    scanf(" %[^\n]*c", findName);
    
    while(person->next != NULL)
    {
        if(strcmp(findName, person->lname) == 0)
        {
            printf("The number associated with %s %s", person->fname, person->lname);
            printf(" is ");
            puts(person->number);
            found = true;
        }
        person = person->next;
    }
    if(found != true)
    {
        printf("The name inserted was not found.\n");
    }
}

void delete_all()
{
  struct node *person = malloc(sizeof(struct node));
  if(head != NULL)
  {
    while(head != NULL)
    {
      person = head;
      head = head->next;
      free(person);
    }
  }
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
 
 
typedef struct ListElement {
    int data;
    struct ListElement * next;
} ListElement_type;
int k=0;
double time_arr[10000];
 
void show(ListElement_type *head);
int list_size(ListElement_type *head);
void push_front(ListElement_type **head, int number);
void push_back(ListElement_type **head, int number);
void push_by_index(ListElement_type **head, int number, int position);
void pop_front(ListElement_type **head);
void pop_back(ListElement_type **head);
void pop_by_index(ListElement_type **head, int position);
void time2get2node(ListElement_type *head, int position);
void merge(ListElement_type *head, ListElement_type *head2);

int main()
{
    ListElement_type *head;
    head = (ListElement_type *)malloc(sizeof(ListElement_type));
    head=NULL;

    ListElement_type *head2;
    head2 = (ListElement_type *)malloc(sizeof(ListElement_type));
    head2 = NULL;

    //by modifying this variable we choose where we want to go
    int element2get2=900000;
    srand(time(NULL)); 

    /*IF YOU WANT TO TEST MERGE() I RECOMMEND MAKING FIRST LIST SMALLER (FOR EG. i < 10) FOR VISIBILITY REASONS*/
    for(int i = 0; i < 1000000; i++)
    {
        push_front(&head,rand());
    }
    for(int i = 0; i < 10; i++)
    {
        push_front(&head2,i);
    }
    // /*TO CHECK MERGE UNCOMMENT 6 ROWS COMMENTED BELOW*/
    // printf("Kolejno wypisujemy liste1 i liste2 przed mergem\n oraz liste 1 i liste 2 po merge'u");
    // show(head);
    // show(head2);
    // merge(head, head2);
    // show(head);
    // show(head2);
    /*TO CHECK TIME UNCOMMENT ALL STUFF COMMENTED BELOW*/ 

    /* TIME TO RANDOM ELEMENT*/
    k=0;
    for(int i = 0; i < 1000; i++)
    {
        time2get2node(head, rand() % 1000000);
    }
    double avg=0;
    for(int i = 0; i < 1000; i++)
    {
        avg+=time_arr[i];
        //printf("\n%f", time_arr[i]);
        time_arr[i]=0;
    }
    avg = avg/1000;
    printf("\nAvg time to get to random elemenet is: %f\n", avg);

    /*TIME TO ELEMENT WE CAN CHOOSE (IN THIS CASE 900000)*/
    k=0;
    for(int i = 0; i < 1000; i++)
    {
        time2get2node(head, element2get2);
    }
    avg=0;
    for(int i = 0; i < 1000; i++)
    {
        avg+=time_arr[i];
        //printf("\n%f", time_arr[i]);
        time_arr[i]=0;
    }
    avg = avg/1000;
    printf("\nAvg time to get to elemenet %d is: %f\n",element2get2, avg);

    /*TIME TO 1000*/
    k=0;
    for(int i = 0; i < 1000; i++)
    {
        time2get2node(head, 1000);
    }
    avg=0;
    for(int i = 0; i < 1000; i++)
    {
        avg+=time_arr[i];
        //printf("\n%f", time_arr[i]);
        time_arr[i]=0;
    }
    avg = avg/1000;
    printf("\nAvg time to get to elemenet %d is: %f\n",1000, avg);

    /*TIME TO 500000*/
    k=0;
    for(int i = 0; i < 1000; i++)
    {
        time2get2node(head, 500000);
    }
    avg=0;
    for(int i = 0; i < 1000; i++)
    {
        avg+=time_arr[i];
        //printf("\n%f", time_arr[i]);
        time_arr[i]=0;
    }
    avg = avg/1000;
    printf("\nAvg time to get to elemenet %d is: %f\n",500000, avg);


    return 0;
}
 
void push_front(ListElement_type **head, int number)
{
    ListElement_type *current;
    current=(ListElement_type *)malloc(sizeof(ListElement_type));
 
    current->data=number;
    current->next=(*head);
    *head=current;
}
 
void push_back(ListElement_type **head, int number)
{
    if(*head==NULL)
    {
        *head = (ListElement_type *)malloc(sizeof(ListElement_type));
        (*head)->data = number;
        (*head)->next = NULL;
    }
    else
    {
        ListElement_type *current=*head;
        while (current->next != NULL) 
        {
            current = current->next;
        }
        current->next = (ListElement_type *)malloc(sizeof(ListElement_type));
        current->next->data = number;
        current->next->next = NULL;
    }
}

void push_by_index(ListElement_type **head, int number, int position)
{
    if(position==0) 
        push_front(head, number);
    else
    {
        if(position==list_size(*head))
            push_back(head, number);
        else
        {
            ListElement_type *current=*head;
            ListElement_type *tmp;
            
            int i=0;
            while (current->next != NULL && i<position-1) 
            {
                current = current->next;
                i++;
            }
            tmp=current->next;
            current->next=(ListElement_type *)malloc(sizeof(ListElement_type));
            current->next->data=number;
            current->next->next=tmp;
        }
    }
}
    
void pop_front(ListElement_type **head)
{
    ListElement_type *tmp=NULL;
    if (*head!=NULL) 
    {
        tmp=(*head)->next;
        free(*head);
        *head=tmp;
    }
}
 
void pop_back(ListElement_type **head)
{
    if((*head)->next==NULL)
        *head=NULL;
    else
    {
        ListElement_type *current=*head;
        while (current->next->next!= NULL) 
        {
            current = current->next;
        }
        free(current->next);
        current->next=NULL;
    }  
}
 
void pop_by_index(ListElement_type **head, int position)
{
    if(position==0) 
        pop_front(head);
    else
    {
        ListElement_type *current=*head;
        ListElement_type *tmp;
        int i=0;
        while (current->next != NULL && i<position-1) {
            current=current->next;
            i++;    
        }
        tmp = current->next;
        current->next = tmp->next;
        free(tmp);
    }
}

void merge(ListElement_type *head, ListElement_type *head2)
{
    ListElement_type *current=head;
    while(current->next != NULL)
    {
        current=current->next;
    }
    current->next=head2;
    head2=NULL;

}
 
void show(ListElement_type *head)
{
    printf("\n");
    if(head==NULL) 
        printf("List is empty");
    else
    {
        ListElement_type *current=head;
        do 
        {
            printf("%i", current->data);
            printf("\n");
            current = current->next;
        }while (current != NULL);//może current->next???
    }
}

void time2get2node(ListElement_type *head, int position)
{
    clock_t begin = clock();
    if(head==NULL) 
        printf("\nList is empty\n");
    else
    {
        ListElement_type *current=head;
        int i=0;
        while(current->next != NULL && i<position-1)
        {
            current=current->next;
            i++;
        }
        if(current->next==NULL)
            printf("\nNo such element\n");
        else
        {
            // printf("\nValue: %d\n",current->next->data);
            // /* here, do your time-consuming job */
            // printf("\nOf node: %d\n", position);
            clock_t end = clock();
            double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            // printf("\nReached in: %f\n",time_spent);
            time_arr[k]=time_spent;
            k++;
        }
    }
}

int list_size(ListElement_type *head)
{
    int counter=0;
    if(head==NULL) 
        return counter;
    else
    {
        ListElement_type *current=head;
        do 
        {
            counter++;
            current = current->next;
        }while (current != NULL);
    }
    return counter;
}
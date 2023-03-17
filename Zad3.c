#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
 
typedef struct ListElement {
    int data;
    struct ListElement * prev;
    struct ListElement * next;
} ListElement_type;

int k=0;
double time_arr[1000];
 
void show(ListElement_type *head);
int list_size(ListElement_type *head);
void push_front(ListElement_type **head, int number);
void push_by_index(ListElement_type **head, int number, int position);
void pop_front(ListElement_type **head);
void pop_by_index(ListElement_type **head, int position);
void time2get2node(ListElement_type *head, int position);
void merge(ListElement_type *head, ListElement_type *head2);

int main()
{
    // W przypadku listy cyklicznej head to inaczej entry point
    ListElement_type *head;
    head = (ListElement_type *)malloc(sizeof(ListElement_type));
    head = NULL;

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
        //push_front(&head,i);

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
    if(*head==NULL)
    {
        *head = (ListElement_type *)malloc(sizeof(ListElement_type));
        (*head)->data = number;
        (*head)->next = (*head);
        (*head)->prev = (*head);
    }
    else
    {
        ListElement_type *current;
        current=(ListElement_type *)malloc(sizeof(ListElement_type));
        
        //hope it's good
        current->data=number;
        current->next=(*head);
        current->prev=(*head)->prev;
        (*head)->prev->next=current;
        (*head)->prev=current;
        *head=current;
    }

}

void push_by_index(ListElement_type **head, int number, int position)
{
    if(position==0) 
        push_front(head, number);
    else
    {
        int listlen = list_size(*head);
        if(position==listlen)   //push front == push back
            push_front(head, number);
        else
        {
            ListElement_type *current=*head;
            ListElement_type *tmp;
            position = position % listlen; // that is if position is 13 and we have 5 elements, 13th position is 3rd 
            int i=0;
            while (current->next != (*head) && i<position-1) 
            {
                current = current->next;
                i++;
            }
            tmp=current->next;
            current->next=(ListElement_type *)malloc(sizeof(ListElement_type));
            current->next->data=number;
            current->next->next=tmp;
            current->next->prev=current;
            tmp->prev=current->next;
        }
    }
}

void pop_front(ListElement_type **head)
{//POP BACK == POP FRONT
    ListElement_type *tmp=NULL;
    if((*head)->next==(*head))//POSSIBLE PROBLEMS
        *head=NULL;
    if (*head!=NULL) 
    {
        tmp=(*head)->next;
        tmp->prev=(*head)->prev;
        free(*head);
        *head=tmp;
    }
}

void pop_by_index(ListElement_type **head, int position)
{
    if(position==0) 
        pop_front(head);
    else
    {
        int listlen = list_size(*head);
        position = position % listlen;
        ListElement_type *current=*head;
        ListElement_type *tmp;
        int i=0;
        while (current->next != (*head) && i<position-1) {
            current=current->next;
            i++;    
        }
        tmp = current->next;
        current->next = tmp->next;
        tmp->next->prev = current;
        free(tmp);
    }
}

void merge(ListElement_type *head, ListElement_type *head2)
{
    // int listlen = list_size(*head2);
    // printf("Listlen: %d\n",listlen);
    // ListElement_type *current=head;
    // while(current->next != NULL)
    // {
    //     current=current->next;
    // }
    // current->next=head2;
    // head2=NULL;
    ListElement_type *tmp;
    head->prev->next=head2;
    head2->prev->next=head;
    tmp=head2->prev;
    head2->prev=head->prev;
    head->prev=tmp;

    // //clean head2
    // for(int i = 0; i < listlen; i++)
    //     pop_front(&head2);
    //free(head2);
    // (*head2)->next = NULL;
    // (*head2)->prev = NULL;
    // //(*head2)->data = NULL;
    // *head2 = NULL;
    // head2 = NULL;

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
        }while (current != head);//może current->next???
    }
}

void time2get2node(ListElement_type *head, int position)
{
    if(head==NULL) 
        printf("\nList is empty\n");
    else
    {
        ListElement_type *current=head;
        int listlen = list_size(head);
        position = position % listlen;  // if we have 5 elements, 13th element is 3rd element 

        int i=0;
        bool forward = (position <= (listlen/2));
        clock_t begin = clock();
        if(forward)
        {
            while(current->next != head && i<position-1)
            {
                current=current->next;
                i++;
            }
        }
        else // if it's faster to go "backwards" we shall do so
        {
            while(current->prev != head && i<((listlen-position)-1))
            {
                current=current->prev;
                i++;
            }   
        }
        // if(current->next == head)
        //     printf("\nNo such element\n");
        // else
        // {
            
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        // if(forward)
        //     printf("\nValue: %d\n",current->next->data);
        // else
        //     printf("\nValue: %d\n",current->prev->data);
        // printf("\nOf node: %d\n", position);
        // printf("\nReached in: %f\n",time_spent);

        time_arr[k]=time_spent;
        k++;
        //}
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
        }while (current != head);
    }
    return counter;
}
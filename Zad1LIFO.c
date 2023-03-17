#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node * next;
} Node_stack;

void push(Node_stack **head, int number);
void pop(Node_stack **head);

int main()
{
    Node_stack *head;
    head = (Node_stack *)malloc(sizeof(Node_stack));
    head = NULL;

    srand(time(NULL));

    for(int i = 0; i < 100; i++)
    {
        push(&head, i);
        printf("Pushed: %d\n",i);
    }
    for(int i = 0; i < 1000; i++)
    {
        pop(&head);
    }

}

void push(Node_stack **head, int number)
{
    Node_stack *current;
    current=(Node_stack *)malloc(sizeof(Node_stack));
 
    current->data=number;
    current->next=(*head);
    *head=current;
}

void pop(Node_stack **head)
{
    Node_stack *tmp=NULL;
    //Node_stack *tmp_data=NULL;

    if (*head!=NULL) 
    {
        printf("Popped: %d\n",(*head)->data);
        tmp=(*head)->next;
        //tmp_data=(*head)->data;
        free(*head);
        *head=tmp;
    }
    
}
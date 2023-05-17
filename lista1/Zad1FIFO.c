#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node * next;
} Node_stack;

void push(Node_stack **head, Node_stack **tail, int number);
void pop(Node_stack **head);

int main()
{
    Node_stack *head;
    head = (Node_stack *)malloc(sizeof(Node_stack));
    head = NULL;

    Node_stack *tail;
    tail = (Node_stack *)malloc(sizeof(Node_stack));
    tail = NULL;

    srand(time(NULL));

    for(int i = 0; i < 100; i++)
    {
        push(&head, &tail, i);
        printf("Pushed: %d\n",i);
    }
    for(int i = 0; i < 1000; i++)
    {
        pop(&head);
    }
}

void push(Node_stack **head, Node_stack **tail, int number)
{
    Node_stack *current;
    current=(Node_stack *)malloc(sizeof(Node_stack));
    
    current->data = number;
    current->next = NULL;

    if((*tail) == NULL)
    {
        (*head) = current;
        (*tail) = current;
    }
    else
    {
        (*tail)->next = current;
        (*tail) = (*tail)->next;
    }
}

void pop(Node_stack **head)
{
    if(*head!=NULL)
    {
        if((*head)->next==NULL)
        {
            printf("Popped: %d\n",(*head)->data);
            *head=NULL;
        }
        else
        {
            Node_stack *current = *head;
            printf("Popped: %d\n", (*head)->data);
            (*head) = (*head)->next;
            free(current);
        }  
    }
}
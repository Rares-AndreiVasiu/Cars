#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
    int info;

    struct _node *prev;

    struct _node *next;
}node;

void init_list(node ** start)
{
    *start = create_node(-1);

    (*start) ->prev = (*start) ->next = *start;
}

void print_list(node *start)
{
    node *p = start->next;

    if(p == start)
    {
        printf("empty");
    }
    else
    {
        while(p != start)
        {
            printf("%d ", p->info);

            p = p -> next;
        }
    }
}

void addNode(node *new, node *start)
{
    new->next = start->next;

    start->next->prev = new;

    new->prev = start;

    start->next=new;
}

void delete(int info, node *start)
{
    node *target = search(info, start);

    if(target)
    {
        target ->prev->next = target->next;

        target->next->prev = target->prev;

        free(target);
    }
}

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXLINE 4096

typedef struct _node
{
    char title[512];

    int year;

    long long budget;

    struct _node *next;

} node;

node *create_node(int year, const char *title, long long budget)
{
    node *p = (node *)malloc(sizeof(node));

    if (p == NULL)
    {
        perror("Error allocating memory!");

        exit(0);
    }

    p->year = year;

    strncpy(p->title, title, strlen(title));

    p->budget = budget;

    return p;
}

void print(node *head)
{
    node *current;

    if (head == NULL)
    {
        printf("Empty list!\n");
    }
    else
    {
        for (current = head; current != NULL; current = current->next)
        {
            printf("Year: %d, Title: %s, Buudget: %lld\n\n", current->year,
                   current->title, current->budget);
        }
    }
}

void add_to_front(node **head, node **tail, node *node_to_add)
{
    node_to_add->next = *head;

    if (NULL == *head)
    {
        *tail = node_to_add;
    }

    *head = node_to_add;
}

void init_list(node **head, node **tail)
{
    *head = *tail = NULL;
}

void add_to_back(node **head, node **tail, node *node_to_add)
{
    if (*tail == NULL)
    {
        *head = node_to_add;
    }
    else
    {
        (*tail)->next = node_to_add;
    }

    *tail = node_to_add;

    node_to_add->next = NULL;
}

void add_sorted(node **head, node **tail, node *node_to_head)
{
    if ((!*head) || (node_to_head -> year < (*head) -> year))
    {
        add_to_front(head, tail, node_to_head);
    }
    else
    {
        if (node_to_head -> year == (*head) -> year)
        {
            if (strcmp(node_to_head -> title, (*head) -> title) < 0)
            {
                add_to_front(head, tail, node_to_head);
            }
        }
        else
        {
            if (node_to_head -> year > (*tail) -> year)
            {
                add_to_back(head, tail, node_to_head);
            }
            else
            {
                node *before, *after;

                before = NULL;

                after = *head;

                while ((after -> year < node_to_head -> year) ||
                       (after -> year == node_to_head -> year &&
                        strcmp(after -> title, node_to_head -> title) < 0))
                {
                    before = after;

                    after = after->next;

                    if (after == NULL)
                    {
                        break;
                    }
                }

                if (after != NULL)
                {
                    node_to_head->next = after;

                    before->next = node_to_head;
                }
            }
        }
    }
}

void delete(node **head, node **tail)
{
    node *current = *head;

    node *nextNode = NULL;

    while(current != NULL)
    {
        nextNode = current -> next;

        free(current);

        current = nextNode;
    }

    *head = NULL;

    *tail = NULL;
}

int main(int argc, char *argv[])
{
    FILE *f;

    node *head, *tail;

    init_list(&head, &tail);

    f = fopen(argv[1], "r");

    if (!f)
    {
        perror("Cannot open the file!");

        exit(0);
    }

    char buffer[MAXLINE];

    // we ignore the first line from the csv file
    fgets(buffer, MAXLINE - 1, f);

    while (!feof(f))
    {
        if (fgets(buffer, MAXLINE - 1, f) == NULL)
        {
            perror("Error reading line!");

            exit(0);
        }
        else
        {
            char *token = strtok(buffer, ",");

            int year = atoi(token);

            char auxBuf[MAXLINE];

            char AuxBufQuotes[MAXLINE];

            // we skip the imbd part
            strtok(NULL, ",");

            token = strtok(NULL, ",");
            
            if(token[0] == '"')
            {
                strcpy(auxBuf, token + 1);

                token = strtok(NULL, "\"");

                strcpy(AuxBufQuotes, token);

                strcat(auxBuf, AuxBufQuotes);
            }
            else
            {
                strcpy(auxBuf, token);
            }

            // we skip the test part
            strtok(NULL, ",");

            // we skip the clean_test part
            strtok(NULL, ",");

            // we skip the binary part
            strtok(NULL, ",");

            token = strtok(NULL, ",");

            long long budget = atoi(token);

            node *node_to_add = create_node(year, auxBuf, budget);

            add_sorted(&head, &tail, node_to_add);

            // printf("Year: %d, Title: %s, Budget: %lld \n\n", year, title, budget);
        }
    }

    print(head);

    delete(&head, &tail);

    print(head);

    return 0;
}

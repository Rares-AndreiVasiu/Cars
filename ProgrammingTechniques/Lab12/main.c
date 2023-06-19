#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAXSIZE 1024

bool checkFullVis(int v[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        if (v[i] != 1)
        {
            return false;
        }
    }
    return true;
}

void greedyPath(int startIndex, int n, char buff[MAXSIZE][MAXSIZE], int roads[MAXSIZE][MAXSIZE])
{
    bool flagPath = true;

    int visited[MAXSIZE];

    int path[MAXSIZE];

    int distance = 0;

    for (int i = 0; i < n; ++i)
    {
        visited[i] = 0;
    }

    for (int i = 0; i < n && flagPath; ++i)
    {
        // we set the flag to check if we find a path
        flagPath = false;

        visited[startIndex] = 1;

        // printf("Start index: %d\n", startIndex);

        path[i] = startIndex;

        int localMin = INT_MAX;

        int index = 0;

        for (int j = 0; j < n; ++j)
        {
            if (visited[j] == 0 && roads[startIndex][j] < localMin && roads[startIndex][j] != -1)
            {
                // printf("we try to go to: %d\n", roads[startIndex][j]);
                // printf("We try to go to: %d\n", index);

                localMin = roads[startIndex][j];

                flagPath = true;

                index = j;
            }
        }

        // if we didn't find a path but the road is still available we are stuck
        if (!flagPath && !checkFullVis(visited, n) && localMin == INT_MAX)
        {
            puts("we have ecountered an invalid path!");

            return;
        }
        else
        {
            // printf("for node: %d the visited status is: %d\n", startIndex, checkFullVis(visited, n));
            startIndex = index;

            if (localMin != INT_MAX)
            {
                distance += localMin;
            }
            // printf("Local min for choice: %d\n\n", localMin);
        }
    }

    // for(int i = 0; i < n; ++ i)
    // {
    //     printf("This node: %d is in the status of visited: %d\n", i, visited[i]);
    // }

    for (int i = 0; i < n; ++i)
    {
        printf("%s -> ", buff[path[i]]);
    }

    printf("%d\n", distance);
}

int main(int argc, char *argv[])
{
    int roads[MAXSIZE][MAXSIZE];

    if (argc < 2)
    {
        perror("Error: there aren't enough arguments");

        exit(EXIT_FAILURE);
    }

    FILE *f = fopen(argv[1], "r");

    if (!f)
    {
        perror("Error while opening the file path!");

        exit(EXIT_FAILURE);
    }

    int n;

    if (fscanf(f, "%d\n", &n) == 1)
    {
        printf("N = %d\n", n);

        char buffer[n][MAXSIZE];
        char s[MAXSIZE];

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                roads[i][j] = -1;
            }
        }

        fgets(s, MAXSIZE, f);

        int index = 0;

        char *token = strtok(s, ",");

        while (token)
        {
            strcpy(buffer[index++], token);

            token = strtok(NULL, ",");
        }

        for (int i = 0; i < n; ++i)
        {
            printf("%s\n", buffer[i]);
        }

        // now we read the nums

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                int x;

                if (fscanf(f, "%d,", &x) == 1)
                {
                    roads[i][j] = x;
                }
            }
        }

        for (int i = 0; i < n; ++i, printf("\n"))
        {
            for (int j = 0; j < n; ++j)
            {
                printf("%d ", roads[i][j]);
            }
        }

        for (int i = 0; i < n; ++i)
        {
            greedyPath(i, n, buffer, roads);
        }
    }
    return 0;
}

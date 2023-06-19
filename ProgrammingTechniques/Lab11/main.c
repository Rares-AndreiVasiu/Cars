#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#define MAXSIZE 4096
#define DBG 0

int a[MAXSIZE][MAXSIZE];

const int di[] = {0, 0, 1, -1};
const int dj[] = {1, -1, 0, 0};

bool foundTrack = false;

bool inside(int i, int j, int rows, int cols)
{
    return i >= 0 && i < rows && j >= 0 && j < cols;
}

void print(int rows, int columns, const char *str)
{
    FILE *fout = fopen(str, "w");

    if (!fout)
    {
        perror("Error while opening the file!");

        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < rows; ++i, fprintf(fout, "\n"))
    {
        for (int j = 0; j < columns; ++j)
        {
            if (a[i][j] == -1)
            {
                fprintf(fout, "#");
            }
            else
            {
                fprintf(fout, "%d ", a[i][j]);
            }
        }
    }
}

void move(int i, int j, int step, int rows, int cols, int iend, int jend, const char *str)
{
    for (int d = 0; d < 4 && !foundTrack; ++d)
    {
        int newI = i + di[d];

        int newJ = j + dj[d];

        if (inside(newI, newJ, rows, cols) && a[newI][newJ] == 0)
        {
            a[newI][newJ] = step;

            if (newI == iend && newJ == jend)
            {
                foundTrack = true;

                print(rows, cols, str);
            }
            else
            {
                move(newI, newJ, step + 1, rows, cols, iend, jend, str);
            }

            a[newI][newJ] = 0;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        perror("Not enough arguments from commandline!");

        exit(EXIT_FAILURE);
    }

    char buffer[MAXSIZE];

    FILE *fp = fopen(argv[1], "r");

    if (!fp)
    {
        perror("Error while opening the file!");

        exit(EXIT_FAILURE);
    }

    fgets(buffer, MAXSIZE - 1, fp);

    const char *ptr = strrchr(buffer, '#');

    /*
        this is stricly the number of the #, ' ', 'E', 'S' max per line
        without including the '\0' at the end
    */
    int rows = 1; // because we already read a line
    int columns = 0;
    int index = 0;
    int istart, jstart;
    int iend, jend;

    columns = (ptr - buffer) + 1;

    while (!feof(fp))
    {
        if (fgets(buffer, columns + 1, fp) != NULL)
        {
            if (strchr(buffer, '#'))
            {
                rows++;
            }
        }
    }

    // we have the # of rows & cols
    char maze[rows][columns + 1];

    fseek(fp, 0, SEEK_SET); // we go back to the beginning to the file

    while (!feof(fp))
    {
        if (fgets(buffer, columns + 1, fp) != NULL)
        {
            if (strchr(buffer, '#'))
            {
                strncpy(maze[index], buffer, columns + 1);

                maze[index][columns + 1] = '\0';

                index++;
            }
        }
    }

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            switch (maze[i][j])
            {
            case ' ':
            {
                a[i][j] = 0;
                break;
            }

            case '#':
            {
                a[i][j] = -1;
                break;
            }

            case 'S':
            {
                a[i][j] = 0;

                istart = i;

                jstart = j;

                break;
            }

            case 'E':
            {
                a[i][j] = 0;

                iend = i;

                jend = j;

                break;
            }
            }
        }
    }

    a[istart][jstart] = 1;

    FILE *fout = fopen(argv[2], "w");

    if (!fout)
    {
        perror("Error while opening the file!");

        exit(EXIT_FAILURE);
    }

    fclose(fout);

    move(istart, jstart, 2, rows, columns, iend, jend, argv[2]);

    if (!foundTrack)
    {
        FILE *fout = fopen(argv[2], "w");

        if (!fout)
        {
            perror("Error while opening the file!");

            exit(EXIT_FAILURE);
        }
        fprintf(fout, "There is now way out! You are forever trapped!");
    }
    return 0;
}

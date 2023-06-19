#ifndef UTILS // we start the declaration of UTILS
#define UTILS

#include "structData.h"

// we check if the user typed correct input
int checkOption(int x)
{
    if (x < 1 || x > 3)
    {
        return 0;
    }

    return 1;
}

//we check if the user option is valid
int checkShapeOption(int x)
{
    if (x < 1 || x > 3)
    {
        return 0;
    }

    return 1;
}

int checkTriangleValidity(point A, point B, point C)
{
    /*
    three points are not collinear
    if the area of the triangle ABC is != 0 => valid triangle
    */

    float determinant = (1.0 / 2.0) * (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));

    return (determinant != 0);
}

int checkCircleValidity(point O, float r)
{
    return (r != 0);
}

int checkRectangleValidity(point A, point B)
{
    /*
        If both of the points are on the same line
        they cannot form a rectangle
    */

    if (A.x == B.x || A.y == B.y)
    {
        return 0;
    }

    return 1;
}

// main menu declaration
void MainMenu()
{
    // system("clear");

    printf("== Welcome to Geometry! ==\n");

    printf("Add Shape: press 1\n");

    printf("Print Shapes: press 2\n");

    printf("Exit Geometry: press 3\n");

    // printf("%i", 0.1 + 0.2==0.3);
}

void ExitGeometry()
{
    // system("clear");

    printf("You are about to leave the programm\n");
    printf("Confirm: press 1\n");
    printf("Abort: press 0\n");

    int exit_option = 0;
    int x = 1;

    if (scanf("%d[^\n]", &exit_option) == 1)
    {
        switch (exit_option)
        {
        case 0:
        {
            MainMenu(&x);
            break;
        }

        default:
        {
            exit(1);

            break;
        }
        }
    }
}

void ShapeSelectorMenu()
{
    // system("clear");

    printf("Add triangle: press 1\n");

    printf("Add circle: press 2\n");

    printf("Add rectangle: press 3\n");
}


void ErrorShape()
{
    puts("Error: your input is incorrect");
}

#endif // we end the declaration of UTILS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "utils.h"

#define DBG 0
#define MAX_SIZE 101

// declare the shape struct holding data
geometricShape_t shapelist[MAX_SIZE];

// function to print all stored shapes
void PrintAllShapes(int n, geometricShape_t p[MAX_SIZE])
{
#if DBG == 1
    printf("Here we print stuff\n");
#endif

    int countT = 0, countC = 0, countR = 0;

    for (int i = 0; i < n; ++i)
    {
        switch (p[i].flag)
        {
        // we print a triangle
        case 1:
        {
            countT++;

            printf("\n%d-th triangle\n", countT);

            printf("P1(%f, %f)\n", p[i].shape.T.p1.x, p[i].shape.T.p1.y);
            printf("P2(%f, %f)\n", p[i].shape.T.p2.x, p[i].shape.T.p2.y);
            printf("P3(%f, %f)\n", p[i].shape.T.p3.x, p[i].shape.T.p3.y);

            break;
        }

        // we print a circle
        case 2:
        {
            countC++;

            printf("\n%d-th circle\n", countC);

            printf("Origin(%f, %f)\n", p[i].shape.C.origin.x, p[i].shape.C.origin.y);
            printf("Radius of the circle: %f\n", p[i].shape.C.radius);

            break;
        }

        // we print a rectangle
        case 3:
        {
            countR++;

            printf("\n%d-th rectangle\n", countR);

            printf("P1(%f, %f)\n", p[i].shape.R.A.x, p[i].shape.R.A.y);
            printf("P2(%f, %f)\n", p[i].shape.R.B.x, p[i].shape.R.B.y);

            break;
        }
        }
    }
}

// basic constructor for triangles case
geometricShape_t initTriangle(geometricShape_t p)
{
    p.flag = 0;

    p.shape.T.p1.x = 0;
    p.shape.T.p1.y = 0;

    p.shape.T.p2.x = 0;
    p.shape.T.p2.x = 0;

    p.shape.T.p3.x = 0;
    p.shape.T.p3.x = 0;

    return p;
}

// basic constructor for circle case
geometricShape_t initCircle(geometricShape_t p)
{
    p.flag = 0;

    p.shape.C.origin.x = 0;
    p.shape.C.origin.y = 0;

    p.shape.C.radius = 0;

    return p;
}

// basic constructor for rectangle case
geometricShape_t initRectangle(geometricShape_t p)
{
    p.flag = 0;

    p.shape.R.A.x = 0;
    p.shape.R.A.y = 0;

    p.shape.R.B.x = 0;
    p.shape.R.B.y = 0;

    return p;
}

int main()
{
    int index = 0;

    do
    {
        int userOption = -1;

        while (userOption == -1)
        {
            MainMenu();

            if (scanf("%d[^\n]", &userOption) == 1)
            {
                if (!checkOption(userOption))
                {
                    userOption = -1;
                }
            }
        }

#if DBG == 1
        printf("User options inputed: %d\n", userOption);
#endif

        switch (userOption)
        {
            case 1:
            {
                // in this case we let the user to choose what shape to be entered

                ShapeSelectorMenu();

                int shapeOption = 0;

                if (scanf("%d[^\n]", &shapeOption) == 1)
                {
                    if (checkOption(shapeOption))
                    {
                        switch (shapeOption)
                        {
                            case 1:
                            {
                                puts("=== Let's add a triangle! ===");

                                puts("Introduce 3 points in 2D");

                                point A, B, C;

                                printf("P1(x, y): ");

                                if (scanf("%f %f%*[^\n]", &A.x, &A.y) != 2)
                                {
                                    ErrorShape();

                                    break;
        #if DBG == 1
                                    printf("Stored data: %f %f\n", shapelist[index].shape.T.p1.x, shapelist[index].shape.T.p1.y);
                                    printf("Read nums: %f %f\n", x1, y1);
        #endif
                                }

                                printf("P2(x, y): ");

                                if (scanf("%f %f%*[^\n]", &B.x, &B.y) != 2)
                                {
                                    ErrorShape();

                                    break;
                                }

                                printf("P3(x, y): ");

                                if (scanf("%f %f%*[^\n]", &C.x, &C.y) != 2)
                                {
                                    ErrorShape();

                                    break;
                                }

                                // check if triangle ABC is valid
                                if (checkTriangleValidity(A, B, C))
                                {
                                    shapelist[index] = initTriangle(shapelist[index]);

                                    shapelist[index].flag = TRIANGLE;

                                    shapelist[index].shape.T.p1.x = A.x;
                                    shapelist[index].shape.T.p1.x = A.x;

                                    shapelist[index].shape.T.p2.x = B.x;
                                    shapelist[index].shape.T.p2.y = B.y;

                                    shapelist[index].shape.T.p3.x = C.x;
                                    shapelist[index].shape.T.p3.y = C.y;

                                    index++;
                                }

                                break;
                            }

                            case 2:
                            {
                                puts("=== Let's add a circle! ===");

                                puts("Introduce the origin in 2D");

                                point Origin;

                                float r;

                                printf("O(x, y): ");

                                if (scanf("%f %f%*[^\n]", &Origin.x, &Origin.y) != 2)
                                {
                                    ErrorShape();

                                    break;
                                }

                                printf("Radius: ");

                                if (scanf("%f%*[^\n]", &r) != 1)
                                {
                                    ErrorShape();

                                    break;
                                }

                                if (checkCircleValidity(Origin, r))
                                {
                                    shapelist[index] = initCircle(shapelist[index]);

                                    shapelist[index].flag = CIRCLE;

                                    shapelist[index].shape.C.origin.x = Origin.x;
                                    shapelist[index].shape.C.origin.y = Origin.y;

                                    shapelist[index].shape.C.radius = r;

                                    index++;
                                }
                                break;
                            }

                            case 3:
                            {
                                puts("=== Let's add a rectangle! ===");

                                puts("Introduce 2 points in 2D");

                                point A, B;

                                printf("P1(x, y): ");

                                if (scanf("%f %f%*[^\n]", &A.x, &B.y) != 2)
                                {
                                    ErrorShape();

                                    break;
                                }

                                printf("P2(x, y): ");

                                if (scanf("%f %f[^\n]", &B.x, &B.y) != 2)
                                {
                                    ErrorShape();

                                    break;
                                }

                                if (checkRectangleValidity(A, B))
                                {
                                    shapelist[index] = initCircle(shapelist[index]);

                                    shapelist[index].flag = RECTANGLE;

                                    shapelist[index].shape.R.A.x = A.x;
                                    shapelist[index].shape.R.A.y = A.y;

                                    shapelist[index].shape.R.B.x = B.x;
                                    shapelist[index].shape.R.B.y = B.y;

                                    index++;
                                }

                                break;
                            }
                        }
                    }
                }
                
                else
                {
                    ErrorShape();

                    break;
                }

                break;
            }

            case 2:
            {
                // print all stored shapes in shapelist

                PrintAllShapes(index, shapelist);

                break;
            }

            case 3:
            {
                // double check if the user 100% wants to exit
                ExitGeometry();

                break;
            }
        }

    } while (1);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXSIZE 1024

void line(double xStart, double yStart, double xFinal, double yFinal)
{
    printf("<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"blue\" stroke-width=\"2\" />\n",
    xStart, yStart, xFinal, yFinal);
}

void Koch(int n, float xStart, float yStart, float xFinal, float yFinal)
{
    if(n == 0)
    {
        line(xStart, yStart, xFinal, yFinal);
    }
    else
    {
        float deltaX = xFinal - xStart;
        float deltaY = yFinal - yStart;

        float x3 = xStart + deltaX / 3.0;
        float y3 = yStart + deltaY / 3.0;

        float x4 = 0.5 * (xStart + xFinal) + sqrt(3) * (yStart - yFinal) / 6.0;
        float y4 = 0.5 * (yStart + yFinal) + sqrt(3) * (xFinal - xStart) / 6.0;

        double x5 = xStart + 2.0 * deltaX / 3.0;
        double y5 = yStart + 2.0 * deltaY / 3.0;

        Koch(n - 1, xStart, yStart, x3, y3);

        Koch(n - 1, x3, y3, x4, y4);

        Koch(n - 1, x4, y4, x5, y5);

        Koch(n - 1, x5, y5, xFinal, yFinal);

    }
    return;
}

int main()
{
    printf("<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");

    int n;

    if(scanf("%d", &n) == 1)
    {
        Koch(n, 0, 0, 100, 100);
    }
    printf("</svg>");

    return 0;
}

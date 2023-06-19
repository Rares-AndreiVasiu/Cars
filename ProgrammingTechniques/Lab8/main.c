#include <stdio.h>
#include <stdarg.h>
#include <limits.h>

void foo(char *fmt, ...)
{
    va_list ap;

    int d;

    char c;
    
    char *s;

    va_start(ap, fmt);

    while(*fmt)
    {
        switch (*fmt++)
        {
            case 's':
            {
                s = va_arg(ap, char *);

                printf("string %s\n", s);

                break;
            }

            case 'd':
            {
                d = va_arg(ap, int);

                printf("int %d\n", d);

                break;
            }

            case 'c':
            {
                c = (char) va_arg(ap, int);

                printf("char %c\n", c);

                break;
            }
        }
        va_end(ap);
    }
}

void minMax(int counter, ...)
{
    va_list ap;

    va_start(ap, counter);

    int num;

    int minimum = INT_MAX;

    int maximum = INT_MIN;

    for(int i = 1; i <= counter; ++ i)
    {
        num = va_arg(ap, int);

        if(num > maximum)
        {
            maximum = num;
        }

        if(num < minimum)
        {
            minimum = num;
        }
    }

    printf("The minimum element is: %d\n", minimum);

    printf("The maximum element is: %d\n", maximum);
}

int main()
{
    foo("ds", 11, "Renault Clio 4 Trophy");

    minMax(7, 15, 2, -3, -1, 9, 6, 7);  

    return 0;
}

maximum = 2

1 2 3

num = 1 => maximum = num

num = 2 => maximum = num

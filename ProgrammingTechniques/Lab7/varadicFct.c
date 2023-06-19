#include <stdio.h>
#include <stdarg.h>

void foo(char *fmt, ...) /* '...' is C syntax for a variadic function */
{
    va_list ap;

    int d;
    
    char c;
    
    char *s;

    va_start(ap, fmt);
    
    while (*fmt)
    {
        switch(*fmt)
        {
            //we have 
            case 'l':
            {
                fmt++;

                switch (*fmt++)
                {
                    case 'u':
                    {
                        unsigned long x = (unsigned long) va_arg(ap, unsigned long);

                        printf("unsigned long %lu\n", x);

                        break;
                    }

                    case 'f':
                    {
                        double y = (double) va_arg(ap, double);

                        printf("long float %.14lf\n", y);

                        break;
                    }
                }
                break;
            }

            default:
            {
                switch (*fmt++)
                {
                    case 's': /* string */
                    {
                        s = va_arg(ap, char *);

                        printf("string %s\n", s);
                        
                        break;
                    }
                    
                    case 'd': /* int */
                    {
                        d = va_arg(ap, int);
                        
                        printf("int %d\n", d);
                        
                        break;
                    }

                    case 'c': /* char */
                    {
                        /* need a cast here since va_arg only
                        takes fully promoted types */
                        c = (char)va_arg(ap, int);
                        
                        printf("char %c\n", c);
                        
                        break;
                    }

                    case 'u':
                    {	
                        unsigned num = (unsigned) va_arg(ap, unsigned);

                        printf("unsigned %u\n", num);

                        break;
                    }	

                    case 'f':
                    {
                        double ft = (double) va_arg(ap, double);

                        printf("floating number %lf\n", ft);

                        break;
                    }
                }
            }
        }
    va_end(ap);
    }
}

double average(int n, ...)
{
    va_list ap;

    va_start(ap, n);

    double averageN = 0.0;

    double sum = 0;

    int counter = 0;

    double num = 0.0;

    while((num = va_arg(ap, double)) >= 0)
    {
        counter++;

        sum += (double) num;
    }

    if(counter == n && n > 0)
    {
        averageN = sum / n;
    }
    else
    {
        puts("Incorrect number of elements!");
    }

    return averageN;
}

int main()
{   
    double a = average(5, 6.0, 18.0, 19.0, 2.0, -2.3);

    printf("%lf\n", a);

    return 0;
}

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

/*
sin () , cos(),
ceil () , floor () , fabs () , log() and sqrt () .
*/

double (*nameFunction[7])(double x);


char *names[20];

void init()
{
    names[0] = "sin";

    names[1] = "cos";

    names[2] = "ceil";

    names[3] = "floor";

    names[4] = "fabs";

    names[5] = "log";

    names[6] = "sqrt";

    nameFunction[0] = &sin;

    nameFunction[1] = &cos;

    nameFunction[2] = &ceil;

    nameFunction[3] = &floor;

    nameFunction[4] = &fabs;

    nameFunction[5] = &log;

    nameFunction[6] = &sqrt;
}

void mainMenu()
{
    puts("=== Math function selector ===");

    for(int i = 0; i < 7; ++ i)
    {
        printf("To choose: %s, press %d\n",names[i], i);
    }
}


int main()
{
    init();

    mainMenu();

    int option = 0;

    bool validInput = false;

    while(!validInput)
    {
        printf("Enter you option: ");
        if(scanf("%d[^\n]", &option) == 1)
        {
            if(option >= 0 && option < 7)
            {
                validInput = true;
            }
        }
    }

    printf("your option: %d\n", option);

    double num = 0.0;

    bool flag = false;

    while(!flag)
    {
        printf("Enter your number: ");

        if(scanf("%lf[^\n]", &num) == 1)
        {
            flag = true;
        }
    }

    printf("The result is equal to: %lf\n", nameFunction[option](num));

    return 0;
}

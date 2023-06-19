#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <ctype.h>

#define POSITIVE        0       
#define NO_INPUT        1
#define TOO_LONG_INPUT  2
#define SMALL_BUFFER    3

#define DBG 0

typedef struct _class
{
    char firstName[512];
    char lastName[512];

    int grade;
}student_t;

student_t *students;

// functions used to hold the programm for X seconds
void waitForSeconds(unsigned int seconds)
{
    unsigned int retTime = time(0) + seconds;

    while(time(0) < retTime);
}

void ExitProgramm()
{
    printf("You are about to leave the program. Cheers!\n");

    waitForSeconds(2);

    exit(EXIT_SUCCESS);
}

void mainMenu()
{
    printf("===== Student Register =====\n");
    
    puts("Exit program:                             0");

    puts("Give N, the numeber of students:          1");

    puts("Enter the data for students:              2");

    puts("Print the class in alphabetical order:    3");

    puts("Print ranking of class based on grades:   4");

    puts("Print top 3 best students:                5");
}

static int getLine(char *prompt, char *buffer, size_t bufferSize)
{
    int character, temp;

    if(bufferSize < 1)
    {
        return SMALL_BUFFER;
    }

    if(prompt != NULL)
    {
        printf("%20s", prompt);

        fflush(stdout);
    }

    if(fgets(buffer, bufferSize, stdin) == NULL)
    {
        return NO_INPUT;
    }

    // Catch any occurrences of '0' in the input data flow.
    size_t length = strlen(buffer);

    if(length < 1)
    {
        return NO_INPUT;
    }

    /*
        There will be no newline if it was too long. In such scenario = >
        flush to the very end of the line so 
        that the surplus does not interfere with the next call.
    */

    if(buffer[length - 1] != '\n')
    {
        temp = 0;

        while((character = getchar() != '\n') && (character != EOF))
        {
            temp = 1;
        }

        return (temp == 1) ? TOO_LONG_INPUT : POSITIVE;
    }

    //else remove newline and return to the caller

    buffer[length - 1] = '\0';

    return POSITIVE;
}

bool checkValidUserInput(const char *input)
{
    int number = atoi(input);

    //check if the choice is a valid number from {0, 1, 2, 3, 4, 5}
    if(number >= 0 && number <= 5)
    {
        char numberToString[2];

        //convert back to string to check if input is the same with its conversion
        sprintf(numberToString, "%d", number);

        if(strcmp(numberToString, input) == 0)
        {
            return true;
        }
    }
    return false;
}

bool checkValidNumber(const char *input)
{
    int number = atoi(input);

    char numberToString[512];

    //convert back to string to check if input is the same with its conversion
    sprintf(numberToString, "%d", number);

    if(strcmp(numberToString, input) == 0)
    {
        return true;
    }

    return false;
}

bool checkName(const char *name)
{
    if(name == NULL || name[0] == '\0')
    {
        return false;
    }

    while(*name != '\0')
    {
        if(!isalpha(*name) && *name != ' ')
        {
            return false;
        }
        name++;
    }
    
    return true;
}

bool checkGrade(const char *grade)
{
    if(checkValidNumber(grade))
    {
        int num = atoi(grade);

        if(num >= 1 && num <= 10)
        {
            return true;
        }
    }
    return false;
}

void setNumberOfStudents(int *n)
{
    printf("\nHere we set the number of students\n\n");

    bool flagValidNumberOfStudents = false;

    char bufferNum[512];

    while(!flagValidNumberOfStudents)
    {
        int streamNumberOfStudentsCheck = getLine("Introduce the number of students in the class: ", bufferNum, sizeof(bufferNum));

        if(streamNumberOfStudentsCheck == POSITIVE && checkValidNumber(bufferNum))
        {
            if(atoi(bufferNum) > 0)
            {
                flagValidNumberOfStudents = true;
            }
            else
            {
                fprintf(stderr, "Error: Negative number of students!\n");
            }
        }
        else
        {
            fprintf(stderr, "Error: Wrong input!\n");
        }
    }

    *n = atoi(bufferNum);
}

void addStudents(int *n)
{
    if(*n > 0)
    {
        printf("\nHere we add data about the students\n\n");

        students = malloc(sizeof(student_t) * (*n + 1));

        if(!students)
        {
            perror("Error while allocating memory");

            return;
        }

        for(int i = 1; i <= *n; ++ i)
        {
            char buffereFirstName[512], bufferLastName[512], bufferGrade[3];

            bool flagUserNewDataValidity = false;

            while(!flagUserNewDataValidity)
            {
                printf("Input data for the %d-th student:\n", i);

                int streamFirstNameCheck = getLine("Enter first name of user: ", buffereFirstName, sizeof(buffereFirstName));

                int streamLastNameCheck = getLine("Enter last name of user: ", bufferLastName, sizeof(bufferLastName));

                int streamGradeCheck = getLine("Enter grade of user: ", bufferGrade, sizeof(bufferGrade));

                if(streamFirstNameCheck == POSITIVE && streamLastNameCheck == POSITIVE && streamGradeCheck == POSITIVE)
                {
                    if(checkName(buffereFirstName) && checkName(bufferLastName) && checkGrade(bufferGrade))
                    {
                        flagUserNewDataValidity = true;
                    }
                    else
                    {
                        puts("Incorrect input!");
                    }
                }
                else
                {
                    puts("Invalid input!");
                }
            }

            printf("\n");

            int conversion = atoi(bufferGrade);

            strcpy(students[i].firstName, buffereFirstName);

            strcpy(students[i].lastName, bufferLastName);

            students[i].grade = conversion;
        }        
    }
    else
    {
        puts("No number of students entered!");
        return;
    }
}

void swap(student_t *a, student_t *b)
{
    student_t *aux = malloc(sizeof(student_t));

    strcpy(aux->firstName, a->firstName);
    strcpy(aux->lastName, a->lastName);
    aux->grade = a->grade;

    strcpy(a->firstName, b->firstName);
    strcpy(a->lastName, b->lastName);
    a->grade = b->grade;

    strcpy(b->firstName, aux->firstName);
    strcpy(b->lastName, aux->lastName);
    b->grade = aux->grade; 
}

void printAlphabetic(int *n)
{
    printf("\nHere we print in alphabetical order\n\n");

    if(*n > 0)
    {
        for(int i = 1; i < *n; ++ i)
        {
            for(int j = i + 1; j <= *n; ++ j)
            {
                int compareLastNames = strcmp(students[i].lastName, students[j].lastName);

                if(compareLastNames == 0)
                {
                    if(strcmp(students[i].firstName, students[j].firstName) > 0)
                    {
                        swap(&students[i], &students[j]);
                    }
                }
                else
                {
                    if(compareLastNames > 0)
                    {
                        swap(&students[i], &students[j]);
                    }
                }
            }
        }

        for(int i = 1; i <= *n; ++ i)
        {
            printf("The %d-th student: \n", i);

            printf("First name: %s\n", students[i].firstName);
            
            printf("Last name: %s\n", students[i].lastName);
            
            printf("Final Grade: %d\n\n", students[i].grade);
        }
    }
    else
    {
        printf("\nNot entered the number of students!\n");

        return;
    }
}

void printRankingGrades(int *n)
{
    printf("\nHere we print the top students grades\n\n");

    if(*n > 0)
    {
        for(int i = 1; i < *n; ++ i)
        {
            for(int j = i + 1; j <= *n; ++ j)
            {
                if(students[i].grade < students[j].grade)
                {
                    swap(&students[i], &students[j]);
                }
            }
        }

        for(int i = 1; i <= *n; ++ i)
        {
            printf("The %d-th student: \n", i);

            printf("First name: %s\n", students[i].firstName);
            
            printf("Last name: %s\n", students[i].lastName);
            
            printf("Final Grade: %d\n\n", students[i].grade);
        }
    }
    else
    {
        printf("\nNot entered the number of students!\n");

        return;
    }
}

void printTopThree(int *n, int *flag)
{
    printf("\nHere we print the top 3's G's\n\n");

    if(*n > 0)
    {
        if(*flag != 0)
        {
            // we already performed the sorting reagarding grades

            for(int i = 1; i <= 3; ++ i)
            {
                printf("The %d-th student: \n", i);

                printf("First name: %s\n", students[i].firstName);
                
                printf("Last name: %s\n", students[i].lastName);
                
                printf("Final Grade: %d\n\n", students[i].grade);
            }
        }
        else
        {
            for(int i = 1; i < *n; ++ i)
            {
                for(int j = i + 1; j <= *n; ++ j)
                {
                    if(students[i].grade < students[j].grade)
                    {
                        swap(&students[i], &students[j]);
                    }
                }
            }
            
            *flag = 1;

            for(int i = 1; i <= 3; ++ i)
            {
                printf("The %d-th student: \n", i);

                printf("First name: %s\n", students[i].firstName);
                
                printf("Last name: %s\n", students[i].lastName);
                
                printf("Final Grade: %d\n\n", students[i].grade);
            }
        }
    }
    else
    {
        puts("Not set the number of students");
        return;
    }
}

void handleUserChoice(int *option, int *n, int *flag)
{
    switch (*option)
    {
        case 0:
        {
            ExitProgramm();
            break;
        }

        case 1:
        {
            setNumberOfStudents(n);

#if DBG == 1
            printf("---- The inputed number of students is: %d\n", *n);
#endif 
            break;
        }

        case 2:
        {
            addStudents(n);
            break;
        }

        case 3:
        {
            printAlphabetic(n);
            break;
        }

        case 4:
        {
            printRankingGrades(n);
            *flag = 1;
            break;
        }

        case 5:
        {
            printTopThree(n, flag);
            break;
        }
    }
}

int main()
{
    int n = 0;
    int flagSortedGrades = 0;

    do
    {
        bool flagValidUserInput = false;

        char userOption[2];

        mainMenu();

        while(!flagValidUserInput)
        {
            int streamInputCheck = getLine("Enter you option: ", userOption, sizeof(userOption));

            if(streamInputCheck == POSITIVE && checkValidUserInput(userOption))
            {
                flagValidUserInput = true;
            }
            else
            {
                printf("Error: incorrect user option in menu!\n");
            }
        }

        int opt = atoi(userOption);

        handleUserChoice(&opt, &n, &flagSortedGrades);

    } while (true);
}

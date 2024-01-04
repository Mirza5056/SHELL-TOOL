#include <stdio.h>
#include <stdlib.h>
#include <string.h>
double addition(double num1, double num2) 
{
    return num1 + num2;
}
double subtraction(double num1, double num2) 
{
    return num1 - num2;
}
double multiplication(double num1, double num2) 
{
    return num1 * num2;
}
double division(double num1, double num2) 
{
    if (num2 != 0) 
    {
        return num1 / num2;
    } else 
    {
        printf("Error: Division by zero\n");
        return 0;
    }
}
int main() 
{
    printf("Shell-Tool 8.0.32\n\n Copyright (c) 2019, 2024, Kamran Akthar and its affiliates.\n Type '/help' or '/?' for help; '/quit' to exit.\n ");
    char input[100];
    char operation[6];
    double num1, num2;
    char *promt="MySHL TS>";
    char *lineptr;
    size_t n=0;
    while (1) 
    {
        printf("%s ", promt);
        fgets(input, sizeof(input), stdin);
        //getline(&lineptr,&n,stdin); 

        sscanf(input, "%s %lf %lf", operation, &num1, &num2);

        if (strcmp(operation, "add") == 0) 
        {
            printf("Result: %.2lf\n\n", addition(num1, num2));
        } 
        else if (strcmp(operation, "sub") == 0) 
        {
            printf("Result: %.2lf\n\n", subtraction(num1, num2));
        } 
        else if (strcmp(operation, "mul") == 0) 
        {
            printf("Result: %.2lf\n\n", multiplication(num1, num2));
        } 
        else if (strcmp(operation, "div") == 0) 
        {
            printf("Result: %.2lf\n\n", division(num1, num2));
        } 
        if(strcmp(operation, " ")==0)
        {
            printf("Invalid operation\n\n");
        } 
        if(strcmp(operation, "/exit")==0)
        {
          printf("Bye!!\n");
          break;
        }
        if(strcmp(operation, "/quit")==0)
        {
          printf("Bye!!\n");
          break;
        }
        if(strcmp(operation, "/help")==0)
        {
          printf("- /(+)         For doing addition use : add 10 20.\n");
          printf("- /(-)         For doing subtraction use : sub 10 20.\n");
          printf("- /(*)         For doing multiplicatiion use : mul 10 20.\n");
          printf("- /(/)         For doing divison use : div 10 20.\n");
          printf("--version      To see version and Shell details.\n");
          printf("- /exit        Exist the Shell-Tool, same as quit.\n");
        }
        if(strcmp(operation,"--version")==0)
        {
          printf("version 2.01.5\n\n");
        }
        //printf("Do you want to exit? (y/n): ");
        //fgets(input, sizeof(input), stdin);

        if (input[0] == 'y' || input[0] == 'Y') 
        {
            break;
        }
    }
    return 0;
}
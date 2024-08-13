#include "headers.h"

char **tokens(char *INPUT)
{
    char Copy[4096];
    strcpy(Copy, INPUT);
    char Delimiters[10] = " \t\n";
    char *Commands = strtok(Copy, Delimiters);
    int tokesns = 0;
    while (Commands != NULL)
    {
        tokesns++;
        Commands = strtok(NULL, Delimiters);
    }
    char **COMMAND = (char **)malloc(sizeof(char *) * (tokesns + 1));
    for (int i = 0; i < (tokesns + 1); i++)
    {
        COMMAND[i] = (char *)malloc(sizeof(char) * 1000);
    }
    char Copie[4096];
    strcpy(Copie, INPUT);
    char *Cammand = strtok(Copie, Delimiters);
    int i = 0;
    while (Cammand != NULL)
    {
        strcpy(COMMAND[i], Cammand);
        printf("%c", COMMAND[i][strlen(COMMAND[i])]);
        Cammand = strtok(NULL, Delimiters);
        i++;
    }
    COMMAND[i] = NULL;
    return COMMAND;
}
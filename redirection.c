#include "headers.h"

void GoDescs(int *INPUTFD, int *OUTPUTFD)
{
    *INPUTFD = dup(0);
    *OUTPUTFD = dup(1);
    return;
}
int redirect(char **INPUT)
{
    int answer = 1000000;
    int i = 0;
    while (INPUT[i] != NULL)
    {
        if (strcmp(INPUT[i], "<") == 0)
        {
            if (answer > i)
            {
                answer = i;
            }
            answer = i;
            char *INPUTFILE = (char *)malloc(sizeof(char) * 1000);
            strcpy(INPUTFILE, INPUT[i + 1]);
            struct stat filestat;
            if (stat(INPUTFILE, &filestat) == 0)
            {
                int inputfd = open(INPUTFILE, O_RDONLY);
                dup2(inputfd, 0);
                close(inputfd);
            }
            else
            {
                perror("No such input file found!");
            }
        }
        if (strcmp(INPUT[i], ">") == 0)
        {
            if (answer > i)
            {
                answer = i;
            }
            char *OUTPUTFILE = (char *)malloc(sizeof(char) * 1000);
            strcpy(OUTPUTFILE, INPUT[i + 1]);
            int outputfd = open(OUTPUTFILE, O_WRONLY | O_TRUNC | O_CREAT, 0644);
            dup2(outputfd, 1);
            close(outputfd);
        }
        if (strcmp(INPUT[i], ">>") == 0)
        {
            if (answer > i)
            {
                answer = i;
            }
            char *OUTPUTFILE = (char *)malloc(sizeof(char) * 1000);
            strcpy(OUTPUTFILE, INPUT[i + 1]);
            int outputfd = open(OUTPUTFILE, O_WRONLY | O_APPEND | O_CREAT, 0644);
            dup2(outputfd, 1);
            close(outputfd);
        }
        i++;
    }
    return answer;
}
void ResetDescs(int *INPUTFD, int *OUTPUTFD)
{
    dup2(*INPUTFD, 0);
    dup2(*OUTPUTFD, 1);
    return;
}

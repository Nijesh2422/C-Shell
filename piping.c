#include "headers.h"

void Piping(char *INPUT, const char *HomeDirectory, char *PrevDirectory, FILE *FilePointer, char *input, const char *PATHOFFILE)
{
    int pipecount = 0;
    for (int k = 0; k < strlen(INPUT); k++)
    {
        if (INPUT[k] == '|')
        {
            pipecount += 1;
        }
    }
    char **ARGV = pipetokens(INPUT);
    int i = 0;
    int fd[2];
    int stdo = dup(1);
    int prev_pipe_read = 0;
    while (ARGV[i] != NULL)
    {
        if (pipe(fd) == -1)
        {
            perror("Piping Error");
            exit(EXIT_FAILURE);
        }
        int status;
        pid_t pid = fork();
        if (pid < 0)
        {
            printf("Forking Error");
            return;
        }
        else if (!pid)
        {
            if (i == 0 && pipecount != 0)
            {
                dup2(fd[1], 1);
            }
            else if (i == pipecount)
            {
                dup2(prev_pipe_read, 0);
                char buffer[1000];
            }
            else
            {
                dup2(prev_pipe_read, 0);
                dup2(fd[1], 1);
            }
            Execute(ARGV[i], HomeDirectory, PrevDirectory, FilePointer, ARGV[i], PATHOFFILE);
            exit(0);
        }
        else
        {
            prev_pipe_read = fd[0];
            wait(&status);
            close(fd[1]);
        }
        i++;
    }
}
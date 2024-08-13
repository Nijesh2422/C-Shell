#include "headers.h"

void Execute(char *INPUT, const char *HomeDirectory, char *PrevDirectory, FILE *FilePointer, char *input, const char *PATHOFFILE)
{
    char **ARGV = tokens(INPUT);
    int start = redirect(ARGV);
    if (start != 1000000)
    {
        for (int g = start; ARGV[g] != NULL; g++)
        {
            ARGV[g] = NULL;
        }
    }
    int flag = 0;
    strcpy(prevCommand, ARGV[0]);
    if (!strcmp(ARGV[0], "peek"))
    {
        flag++;
        peek(HomeDirectory, ARGV, PrevDirectory);
    }
    else if (!strcmp(ARGV[0], "warp"))
    {
        flag++;
        WarpUpdate(HomeDirectory, ARGV, PrevDirectory);
    }
    else if (!strcmp(ARGV[0], "exit"))
    {
        flag++;
        pasteventsadd(FilePointer, PATHOFFILE, input);
        exit(0);
    }
    else if (!strcmp(ARGV[0], "pastevents"))
    {
        flag++;
        PASTEVENTSFLAG++;
        if (ARGV[1] != NULL && strcmp(ARGV[1], "execute") == 0)
        {
            Pasteventsexecute(INPUT, HomeDirectory, PrevDirectory, FilePointer, input, PATHOFFILE, ARGV);
        }
        else
        {
            Pastevents(FilePointer, PATHOFFILE, ARGV);
        }
    }
    else if (!strcmp(ARGV[0], "proclore"))
    {
        flag++;
        proclore(ARGV);
    }
    else if (!strcmp(ARGV[0], "seek"))
    {
        flag++;
        seek(ARGV, HomeDirectory, PrevDirectory);
    }
    else if (!strcmp(ARGV[0], "activities"))
    {
        flag++;
        Activities();
    }
    else if (!strcmp(ARGV[0], "ping"))
    {
        flag++;
        ping(ARGV);
    }
    else if (!strcmp(ARGV[0], "bg"))
    {
        flag++;
        bg(ARGV);
    }
    else if (!strcmp(ARGV[0], "fg"))
    {
        flag++;
        fg(ARGV);
    }
    else if (!strcmp(ARGV[0], "iMan"))
    {
        flag++;
        Iman(ARGV);
    }
    else if (!strcmp(ARGV[0], "neonate") && !strcmp(ARGV[1], "-n"))
    {
        flag++;
        Neonate(ARGV);
    }
    if (flag == 0)
    {
        int status;
        pid_t pid = fork();
        if (pid == 0)
        {
            Foreground = getpid();
            if (execvp(ARGV[0], ARGV) == -1)
            {
                printf("ERROR : '%s' is not a valid command\n", ARGV[0]);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            Foreground = pid;
            strcpy(Dofrramingo, ARGV[0]);
            wait(NULL);
            return;
        }
    }
    return;
}
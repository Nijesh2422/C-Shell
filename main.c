#include "headers.h"
char prevCommand[256] = "Hello There";
double time_elapsed = 0;
BackProcess Array = NULL;
char Dofrramingo[256];
pid_t Foreground = 0;
int main()
{
    // Keep accepting commands
    char HomeDirectory[1000];
    getcwd(HomeDirectory, sizeof(HomeDirectory));
    char PrevDirectory[1000];
    strcpy(PrevDirectory, HomeDirectory);
    // CreatBackArray();
    if (signal(SIGINT, Signal_Handler1) == SIG_ERR)
    {
        perror("Error in signal()");
    }
    // if (signal(SIGTSTP, Signal_Handler2) == SIG_ERR)
    // {
    //     perror("Error in signal()");
    // }
    while (1)
    {
        PASTEVENTSFLAG = 0;
        // Print appropriate prompt with username, systemname and directory before accepting input
        prompt(HomeDirectory);
        char PATHTOFILE[4096];
        strcpy(PATHTOFILE, HomeDirectory);
        strcat(PATHTOFILE, "/PASTEVENTS.txt");
        FILE *FilePointer = fopen(PATHTOFILE, "a+");
        char input[4096];
        if (fgets(input, 4096, stdin) == NULL)
        {
            KillAll();
        }
        input[strlen(input) - 1] = '\0';
        CheckBackGrounds();
        char Dune[4096];
        strcpy(Dune, input);
        char *Copy = strdup(input);
        char Delimiters[10] = ";&";
        char *Saveptr = Copy;
        char *Commands = strtok_r(Saveptr, Delimiters, &Saveptr);
        int i = 0;
        int length = 0;
        while (Commands != NULL)
        {
            if (i == 0)
            {
                length += strlen(Commands);
            }
            else
            {
                length += strlen(Commands) + 1;
            }
            i++;
            if (length <= strlen(input))
            {
                if (input[length] == '&')
                {
                    // go to background
                    char *COMMAND = strdup(Commands);
                    BackGround(COMMAND);
                }
                else
                {
                    // piping
                    struct timeval start_time, end_time;
                    int inputfiledescriptor = -1;
                    int outputfiledescriptor = -1;
                    GoDescs(&inputfiledescriptor, &outputfiledescriptor);
                    char *COMMAND = strdup(Commands);
                    gettimeofday(&start_time, NULL);
                    if (strchr(COMMAND, '|'))
                        Piping(COMMAND, HomeDirectory, PrevDirectory, FilePointer, Dune, PATHTOFILE);
                    else
                        Execute(COMMAND, HomeDirectory, PrevDirectory, FilePointer, Dune, PATHTOFILE);
                    gettimeofday(&end_time, NULL);
                    time_elapsed = (double)(end_time.tv_sec - start_time.tv_sec) +
                                   (double)(end_time.tv_usec - start_time.tv_usec) / 1000000.0;
                    ResetDescs(&inputfiledescriptor, &outputfiledescriptor);
                }
            }
            Commands = strtok_r(Saveptr, Delimiters, &Saveptr);
        }
        if (PASTEVENTSFLAG == 0)
        {
            pasteventsadd(FilePointer, PATHTOFILE, input);
        }
        else
        {
            PASTEVENTSFLAG = 0;
        }
    }
}

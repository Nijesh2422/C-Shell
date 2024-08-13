#include "headers.h"

void RealPastExecute(char *input, const char *HomeDirectory, char *PrevDirectory, FILE *FilePointer, const char *PATHOFFILE)
{
    input[strlen(input) - 1] = '\0';
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
                    Piping(COMMAND, HomeDirectory, PrevDirectory, FilePointer, Dune, PATHOFFILE);
                else
                    Execute(COMMAND, HomeDirectory, PrevDirectory, FilePointer, Dune, PATHOFFILE);
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
        pasteventsadd(FilePointer, PATHOFFILE, input);
    }
    else
    {
        PASTEVENTSFLAG = 0;
    }
}

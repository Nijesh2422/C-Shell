#include "headers.h"

void ping(char **INPUT)
{
    int Processid = atoi(INPUT[1]);
    int Signal = atoi(INPUT[2]);
    Signal = Signal % 32;
    if (kill(Processid, Signal) == 0)
    {
        printf("Sent signal %d to process with pid %d\n", Signal, Processid);
    }
    else
    {
        perror("kill");
    }
    return;
}
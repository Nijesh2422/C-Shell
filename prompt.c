#include "headers.h"

void prompt(const char *HomeDirectory)
{
    // Do not hardcode the prmopt
    int glag = 0;
    double rounded_time = round(time_elapsed);
    if (rounded_time > 2)
    {
        glag++;
    }
    const char *UserName = getlogin();
    if (UserName == NULL)
    {
        perror("Failed to retrieve Username\n");
        return;
    }
    char SystemName[1000];
    if (gethostname(SystemName, sizeof(SystemName)) != 0)
    {
        perror("Failed to retrieve System Name\n");
        return;
    }
    char CWD[1000];
    if (getcwd(CWD, sizeof(CWD)) == NULL)
    {
        perror("Failed to retrieve Current Working Directory\n");
        return;
    }
    if (strcmp(CWD, HomeDirectory) == 0)
    {
        if (glag == 0)
            printf("<%s@%s:%s> ", UserName, SystemName, "~");
        else
            printf("<%s@%s:%s %s : %.0fs> ", UserName, SystemName, "~", prevCommand, rounded_time);
    }
    else
    {
        int DifferenceBits = strlen(CWD) - strlen(HomeDirectory);
        if (DifferenceBits >= 0)
        {
            char *DirectoryName = (char *)malloc(sizeof(char) * (DifferenceBits + 6));
            strcpy(DirectoryName, "~");
            strncat(DirectoryName, CWD + strlen(HomeDirectory), DifferenceBits);
            if (glag == 0)
                printf("<%s@%s:%s> ", UserName, SystemName, DirectoryName);
            else
                printf("<%s@%s:%s %s : %.0fs> ", UserName, SystemName, DirectoryName, prevCommand, rounded_time);
        }
        else
        {
            if (glag == 0)
                printf("<%s@%s:%s> ", UserName, SystemName, CWD);
            else
                printf("<%s@%s:%s %s : %.0fs> ", UserName, SystemName, CWD, prevCommand, rounded_time);
        }
    }
    return;
}

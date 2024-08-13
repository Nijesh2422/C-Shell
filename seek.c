#include "headers.h"
int matchesfound = 0;
int somthn = 0;
void seek(char **ARGV, const char *HomeDirectory, char *PrevDirectory)
{
    int i = 0;
    int dflag = 0;
    int fflag = 0;
    int eflag = 0;
    int numberofflags = 0;
    while (ARGV[i] != NULL)
    {
        if (!strcmp(ARGV[i], "-e") || !strcmp(ARGV[i], "-e\n"))
        {
            numberofflags++;
            eflag++;
        }
        if (!strcmp(ARGV[i], "-d") || !strcmp(ARGV[i], "-d\n"))
        {
            numberofflags++;
            dflag++;
        }
        if (!strcmp(ARGV[i], "-f") || !strcmp(ARGV[i], "-f\n"))
        {
            numberofflags++;
            fflag++;
        }
        i++;
    }
    if (dflag != 0 && fflag != 0 || eflag == 1 && fflag == 0 && dflag == 0)
    {
        printf("Error : Invalid Flags\n");
        return;
    }
    char PathtotheDirectory[4096];
    if (ARGV[numberofflags + 2] == NULL || ARGV[numberofflags + 2][0] == '\n')
    {
        getcwd(PathtotheDirectory, sizeof(PathtotheDirectory));
    }
    else if (ARGV[numberofflags + 2][0] == '.')
    {
        getcwd(PathtotheDirectory, sizeof(PathtotheDirectory));
        strncat(PathtotheDirectory, ARGV[numberofflags + 2] + 1, 999);
    }
    else if (ARGV[numberofflags + 2][0] == '~')
    {
        strcpy(PathtotheDirectory, HomeDirectory);
        strncat(PathtotheDirectory, ARGV[numberofflags + 2] + 1, 999);
    }
    char PETH[4096];
    RealSeek(PathtotheDirectory, eflag, fflag, dflag, ARGV[numberofflags + 1], PathtotheDirectory, PETH);
    int kai = matchesfound+somthn;
    if (eflag == 1 && PETH != NULL && matchesfound == 1)
    {
        if (fflag == 1)
        {
            FILE *FilePointer = fopen(PETH, "r");
            if (FilePointer == NULL)
            {
                printf("Missing permissions for task!\n");
                return;
            }
            char BAFFAR[4096];
            while (fgets(BAFFAR, 4096, FilePointer) != NULL)
            {
                printf("%s", BAFFAR);
            }
            fclose(FilePointer);
        }
        if (dflag == 1)
        {
            getcwd(PrevDirectory, sizeof(PrevDirectory));
            if (chdir(PETH) != 0)
            {
                printf("Missing permissions for task!\n");
            }
        }
    }
    else if (kai == 0)
    {
        printf("No match found!\n");
    }
    matchesfound = 0;
    somthn = 0;
    return;
}
void RealSeek(char *PathtotheDirectory, int eflag, int fflag, int dflag, const char *Target, const char *DupeHome, char *PETH)
{
    DIR *DirectoryPointer = opendir(PathtotheDirectory);
    if (DirectoryPointer == NULL)
    {
        return;
    }
    char PrintingPath[4096];
    strncpy(PrintingPath, PathtotheDirectory + strlen(DupeHome), 4096);
    PrintingPath[strlen(PrintingPath)] = '\0';
    struct dirent *entry;
    while ((entry = readdir(DirectoryPointer)) != NULL)
    {
        if (entry->d_name[0] != '.')
        {
            if (strncmp(entry->d_name, Target, strlen(Target)) == 0)
            {
                if (dflag == 1 && entry->d_type == DT_DIR)
                {
                    matchesfound++;
                    snprintf(PETH, 4096, "%s/%s", PathtotheDirectory, entry->d_name);
                    printf(".%s/%s\n", PrintingPath, entry->d_name);
                }
                else if (fflag == 1 && entry->d_type != DT_DIR)
                {
                    matchesfound++;
                    snprintf(PETH, 4096, "%s/%s", PathtotheDirectory, entry->d_name);
                    printf(".%s/%s\n", PrintingPath, entry->d_name);
                }
                else if (dflag == 0 && fflag == 0)
                {
                    somthn++;
                    printf(".%s/%s\n", PrintingPath, entry->d_name);
                }
            }
            char buffer[4096];
            strcpy(buffer, PathtotheDirectory);
            strcat(buffer, "/");
            strcat(buffer, entry->d_name);
            RealSeek(buffer, eflag, fflag, dflag, Target, DupeHome, PETH);
        }
    }
    closedir(DirectoryPointer);
    return;
}
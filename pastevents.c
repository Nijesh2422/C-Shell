#include "headers.h"
int PASTEVENTSFLAG = 0;
void Pasteventsexecute(char *INPUT, const char *HomeDirectory, char *PrevDirectory, FILE *FilePointer, char *input, const char *PATHOFFILE, char **ARGV)
{
    int number = atoi(ARGV[2]);
    char KEMMAND[4096];
    int lines = 0;
    strcpy(KEMMAND, "\0");
    fseek(FilePointer, 0, SEEK_SET);
    while (fgets(KEMMAND, 4096, FilePointer) != NULL)
    {
        lines++;
    }
    number = lines - number;
    fseek(FilePointer, 0, SEEK_SET);
    while (fgets(KEMMAND, 4096, FilePointer) != NULL && number != 0)
    {
        number--;
    }
    char *COMMnd = strdup(KEMMAND);
    COMMnd[strlen(COMMnd) - 1] = '\0';
    RealPastExecute(KEMMAND, HomeDirectory, PrevDirectory, FilePointer, PATHOFFILE);
    if (PASTEVENTSFLAG > 0)
    {
        PASTEVENTSFLAG--;
    }
    if (PASTEVENTSFLAG == 0)
    {
        pasteventsadd(FilePointer, PATHOFFILE, KEMMAND);
    }
    else
    {
        PASTEVENTSFLAG = 0;
    }
    PASTEVENTSFLAG = 1;
}
void pasteventsadd(FILE *FilePointer, const char *PATHOFFILE, char *input)
{
    char *Command = (char *)malloc(sizeof(char) * (strlen(input) + 5));
    strcpy(Command, input);
    strcat(Command, "\n\0");
    int flag = 0;
    if (PASTEVENTSFLAG == 0)
    {
        char KEMMAND[4096];
        int lines = 0;
        strcpy(KEMMAND, "\0");
        fseek(FilePointer, 0, SEEK_SET);
        while (fgets(KEMMAND, 4096, FilePointer) != NULL)
        {
            lines++;
        }
        if (strcmp(KEMMAND, Command))
        {
            if (lines < 15)
            {
                fprintf(FilePointer, "%s", Command);
            }
            else
            {
                char **PASTCOMANDS = (char **)malloc(sizeof(char *) * (lines + 1));
                for (int h = 0; h < (lines + 1); h++)
                {
                    PASTCOMANDS[h] = (char *)malloc(sizeof(char) * 4096);
                }
                fseek(FilePointer, 0, SEEK_SET);
                int nijesh = 0;
                while (fgets(PASTCOMANDS[nijesh], 4096, FilePointer) != NULL)
                {
                    nijesh++;
                }
                strcpy(PASTCOMANDS[nijesh], Command);
                flag++;
                fclose(FilePointer);
                FilePointer = fopen(PATHOFFILE, "w");
                for (int j = 1; j < lines + 1; j++)
                {
                    fprintf(FilePointer, "%s", PASTCOMANDS[j]);
                }
                fclose(FilePointer);
            }
        }
    }
    if (flag == 0 && PASTEVENTSFLAG == 0)
    {
        fclose(FilePointer);
    }
}
void pastevents(FILE *FilePointer)
{
    char KEMMAND[4096];
    while (fgets(KEMMAND, sizeof(KEMMAND), FilePointer) != NULL)
    {
        printf("%s", KEMMAND);
    }
    fclose(FilePointer);
    return;
}
void pasteventspurge(FILE *FilePointer, const char *PATHOFFILE)
{
    fclose(FilePointer);
    FilePointer = fopen(PATHOFFILE, "w");
    fclose(FilePointer);
}
void Pastevents(FILE *FilePointer, const char *PATHOFFILE, char **Command)
{
    int i = 1;
    int fleg = 0;
    while (Command[i] != NULL)
    {

        if (!strcmp(Command[i], "purge\n") || !strcmp(Command[i], "purge"))
        {
            fleg++;
            pasteventspurge(FilePointer, PATHOFFILE);
        }
        i++;
    }
    if (fleg == 0)
    {
        pastevents(FilePointer);
    }
    return;
}

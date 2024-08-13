#include "headers.h"

void WarpUpdate(const char *HomeDirectory, char **Commands, char *PrevDirectory)
{
    int i = 1;
    int flag = 0;
    while (Commands[i] != NULL)
    {
        if (strcmp("~", Commands[i]) == 0)
        {
            getcwd(PrevDirectory, 1000);
            if (chdir(HomeDirectory) == 0)
            {
                printf("%s\n", HomeDirectory);
            }
        }
        else if (strcmp("-", Commands[i]) == 0)
        {
            char Directory[1000];
            getcwd(Directory, 1000);
            if (chdir(PrevDirectory) == 0)
            {
                printf("%s\n", PrevDirectory);
            }
            else
            {
                perror("Error changing Directories");
            }
            strcpy(PrevDirectory, Directory);
        }
        else if (strcmp(".", Commands[i]) == 0)
        {
            getcwd(PrevDirectory, 1000);
            printf("%s\n", PrevDirectory);
        }
        else if (strcmp("..", Commands[i]) == 0)
        {
            getcwd(PrevDirectory, 1000);
            if (chdir("..") == 0)
            {
                char DirectoryName[100];
                getcwd(DirectoryName, 100);
                printf("%s\n", DirectoryName);
            }
            else
            {
                perror("Error Changing Directories");
            }
        }
        else if (Commands[i][0] == '~')
        {
            getcwd(PrevDirectory, 1000);
            char InitDirectoryName[1000];
            strcpy(InitDirectoryName, HomeDirectory);
            if (Commands[i][strlen(Commands[i]) - 1] != '\n')
            {
                strcat(InitDirectoryName, Commands[i] + 1);
            }
            else
            {
                strncat(InitDirectoryName, Commands[i] + 1, strlen(Commands[i]) - 2);
            }
            if (chdir(InitDirectoryName) == 0)
            {
                printf("%s\n", InitDirectoryName);
            }
            else
            {
                perror("Error");
            }
        }
        else if (Commands[i][0] == '/' && Commands[i][1] == 'h' && Commands[i][2] == 'o' && Commands[i][3] == 'm' && Commands[i][4] == 'e')
        {
            char InitDirectoryName[100];
            getcwd(InitDirectoryName, 100);
            strcpy(PrevDirectory, InitDirectoryName);
            char NewDirectoryName[1000];
            if (Commands[i][strlen(Commands[i]) - 1] == '\n')
            {
                Commands[i][strlen(Commands[i]) - 1] = '\0';
            }
            size_t copyLength = strlen(Commands[i]);
            if (copyLength > sizeof(NewDirectoryName) - 1)
            {
                copyLength = sizeof(NewDirectoryName) - 1;
            }
            strncpy(NewDirectoryName, Commands[i], copyLength);
            NewDirectoryName[copyLength] = '\0';
            chdir(NewDirectoryName);
            printf("%s\n", NewDirectoryName);
        }
        else
        {
            char InitDirectory[1000];
            getcwd(InitDirectory, 1000);
            strcpy(PrevDirectory, InitDirectory);
            strcat(InitDirectory, "/");
            if (Commands[i][strlen(Commands[i]) - 1] != '\n')
            {
                strcat(InitDirectory, Commands[i]);
            }
            else
            {
                strncat(InitDirectory, Commands[i], strlen(Commands[i]) - 1);
            }
            if (chdir(InitDirectory) == 0)
            {
                printf("%s\n", InitDirectory);
            }
            else
            {
                perror("Error changing Directories");
            }
        }
        flag++;
        i++;
    }
    if (flag == 0)
    {
        getcwd(PrevDirectory, 1000);
        if (chdir(HomeDirectory) == 0)
        {
            printf("%s\n", HomeDirectory);
        }
        else
        {
            perror("Error");
        }
    }
    return;
}
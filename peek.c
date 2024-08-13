#include "headers.h"
struct FileStruct
{
    char *FileName;
    int filetype;
};
// Add conditions for just peek
struct FileDetails
{
    char permissions[12];
    unsigned long nlink;
    char owner[20];
    char group[20];
    long long size;
    char time[20];
    char *name;
    int filetype;
};
int compareStrings(const void *a, const void *b)
{
    return strcmp((*(struct FileStruct **)a)->FileName, (*(struct FileStruct **)b)->FileName);
}
void mode_to_string(mode_t mode, char *buf)
{
    strcpy(buf, "----------");

    if (S_ISDIR(mode))
        buf[0] = 'd';
    if (S_ISLNK(mode))
        buf[0] = 'l';

    if (mode & S_IRUSR)
        buf[1] = 'r';
    if (mode & S_IWUSR)
        buf[2] = 'w';
    if (mode & S_IXUSR)
        buf[3] = 'x';

    if (mode & S_IRGRP)
        buf[4] = 'r';
    if (mode & S_IWGRP)
        buf[5] = 'w';
    if (mode & S_IXGRP)
        buf[6] = 'x';

    if (mode & S_IROTH)
        buf[7] = 'r';
    if (mode & S_IWOTH)
        buf[8] = 'w';
    if (mode & S_IXOTH)
        buf[9] = 'x';
}
int compareStrings1(const void *a, const void *b)
{
    return strcmp((*(struct FileDetails **)a)->name, (*(struct FileDetails **)b)->name);
}
void peek(const char *HomeDirectory, char **Command, char *PrevDirectory)
{
    char Path[1000] = "\0";
    char Delimiters[4] = " \t";
    int q = 1;
    int aflag = 0;
    int lflag = 0;
    while (Command[q] != NULL)
    {
        if (!strcmp(Command[q], "-a"))
        {
            aflag++;
        }
        else if (!strcmp(Command[q], "-l"))
        {
            lflag++;
        }
        else if (!strcmp(Command[q], "-la"))
        {
            aflag++;
            lflag++;
        }
        else if (!strcmp(Command[q], "-al"))
        {
            aflag++;
            lflag++;
        }
        else
        {
            if (Command[q][0] == '\0')
            {
                getcwd(Command[q], 1000);
            }
            strcpy(Path, Command[q]);
            DIR *DirectoryName = opendir(Command[q]);
            if (lflag == 0)
            {
                int maxFiles = 100;
                int numFiles = 0;
                struct FileStruct **fileNames = (struct FileStruct **)malloc(maxFiles * sizeof(struct FileStruct *));
                struct dirent *entry;
                while ((entry = readdir(DirectoryName)) != NULL)
                {
                    if (numFiles >= maxFiles)
                    {
                        maxFiles *= 2;
                        fileNames = (struct FileStruct **)realloc(fileNames, maxFiles * sizeof(struct FileStruct *));
                    }
                    if ((aflag == 1) || (aflag == 0 && entry->d_name[0] != '.'))
                    {
                        fileNames[numFiles] = (struct FileStruct *)malloc(sizeof(struct FileStruct));
                        fileNames[numFiles]->FileName = strdup(entry->d_name);
                        struct stat FileStat;
                        stat(entry->d_name, &FileStat);
                        if (S_ISDIR(FileStat.st_mode))
                        {
                            fileNames[numFiles]->filetype = 1;
                        }
                        else if (S_ISREG(FileStat.st_mode))
                        {
                            if (FileStat.st_mode & S_IXUSR)
                            {
                                fileNames[numFiles]->filetype = 2;
                            }
                            else
                            {
                                fileNames[numFiles]->filetype = 0;
                            }
                        }
                        numFiles++;
                    }
                }
                closedir(DirectoryName);
                qsort(fileNames, numFiles, sizeof(struct FileStruct *), compareStrings);
                for (int i = 0; i < numFiles; i++)
                {
                    if (fileNames[i]->filetype == 2)
                    {
                        printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET, fileNames[i]->FileName);
                    }
                    else if (fileNames[i]->filetype == 1)
                    {
                        printf(ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, fileNames[i]->FileName);
                    }
                    else
                    {
                        printf(ANSI_COLOR_WHITE "%s\n" ANSI_COLOR_RESET, fileNames[i]->FileName);
                    }
                    free(fileNames[i]);
                }
                free(fileNames);
            }
            else if (lflag == 1)
            {
                int maxFiles = 100;
                int numFiles = 0;
                struct FileDetails **fileNames = (struct FileDetails **)malloc(maxFiles * sizeof(struct FileDetails *));
                struct dirent *entry;
                while ((entry = readdir(DirectoryName)) != NULL)
                {
                    if (numFiles >= maxFiles)
                    {
                        maxFiles *= 2;
                        fileNames = (struct FileDetails **)realloc(fileNames, maxFiles * sizeof(struct FileDetails *));
                    }
                    if ((aflag == 1) || (aflag == 0 && entry->d_name[0] != '.'))
                    {
                        fileNames[numFiles] = (struct FileDetails *)malloc(sizeof(struct FileDetails));
                        fileNames[numFiles]->name = strdup(entry->d_name);
                        struct stat FileStat;
                        stat(entry->d_name, &FileStat);
                        struct passwd *pwd = getpwuid(FileStat.st_uid);
                        struct group *grp = getgrgid(FileStat.st_gid);
                        strcpy(fileNames[numFiles]->time, entry->d_name);
                        mode_to_string(FileStat.st_mode, fileNames[numFiles]->permissions);
                        fileNames[numFiles]->nlink = FileStat.st_nlink;
                        strncpy(fileNames[numFiles]->owner, pwd->pw_name, sizeof(fileNames[numFiles]->owner) - 1);
                        fileNames[numFiles]->owner[sizeof(fileNames[numFiles]->owner) - 1] = '\0';
                        strncpy(fileNames[numFiles]->group, grp->gr_name, sizeof(fileNames[numFiles]->group) - 1);
                        fileNames[numFiles]->group[sizeof(fileNames[numFiles]->group) - 1] = '\0';
                        fileNames[numFiles]->size = FileStat.st_size;
                        strftime(fileNames[numFiles]->time, sizeof(fileNames[numFiles]->time), "%b %d %H:%M", localtime(&FileStat.st_mtime));
                        if (S_ISDIR(FileStat.st_mode))
                        {
                            fileNames[numFiles]->filetype = 1;
                        }
                        else if (S_ISREG(FileStat.st_mode))
                        {
                            if (FileStat.st_mode & S_IXUSR)
                            {
                                fileNames[numFiles]->filetype = 2;
                            }
                            else
                            {
                                fileNames[numFiles]->filetype = 0;
                            }
                        }
                        numFiles++;
                    }
                }
                qsort(fileNames, numFiles, sizeof(struct FileDetails *), compareStrings1);
                closedir(DirectoryName);
                for (int i = 0; i < numFiles; i++)
                {
                    if (fileNames[i]->filetype == 2)
                    {
                        printf("%s %2lu %-8s %-8s %8lld %s " ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET, fileNames[i]->permissions,
                               fileNames[i]->nlink,
                               fileNames[i]->owner,
                               fileNames[i]->group,
                               fileNames[i]->size,
                               fileNames[i]->time, fileNames[i]->name);
                    }
                    else if (fileNames[i]->filetype == 1)
                    {
                        printf("%s %2lu %-8s %-8s %8lld %s " ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, fileNames[i]->permissions,
                               fileNames[i]->nlink,
                               fileNames[i]->owner,
                               fileNames[i]->group,
                               fileNames[i]->size,
                               fileNames[i]->time, fileNames[i]->name);
                    }
                    else
                    {
                        printf("%s %2lu %-8s %-8s %8lld %s " ANSI_COLOR_WHITE "%s\n" ANSI_COLOR_RESET, fileNames[i]->permissions,
                               fileNames[i]->nlink,
                               fileNames[i]->owner,
                               fileNames[i]->group,
                               fileNames[i]->size,
                               fileNames[i]->time, fileNames[i]->name);
                    }
                }
            }
        }
        q++;
    }
    if (!strcmp(Path, "\0"))
    {
        char NEWPATH[1000];
        getcwd(NEWPATH, 1000);
        DIR *DirectoryName = opendir(NEWPATH);
        if (lflag == 0)
        {
            int maxFiles = 100;
            int numFiles = 0;
            struct FileStruct **fileNames = (struct FileStruct **)malloc(maxFiles * sizeof(struct FileStruct *));
            struct dirent *entry;
            while ((entry = readdir(DirectoryName)) != NULL)
            {
                if (numFiles >= maxFiles)
                {
                    maxFiles *= 2;
                    fileNames = (struct FileStruct **)realloc(fileNames, maxFiles * sizeof(struct FileStruct *));
                }
                if ((aflag == 1) || (aflag == 0 && entry->d_name[0] != '.'))
                {
                    fileNames[numFiles] = (struct FileStruct *)malloc(sizeof(struct FileStruct));
                    fileNames[numFiles]->FileName = strdup(entry->d_name);
                    struct stat FileStat;
                    stat(entry->d_name, &FileStat);
                    if (S_ISDIR(FileStat.st_mode))
                    {
                        fileNames[numFiles]->filetype = 1;
                    }
                    else if (S_ISREG(FileStat.st_mode))
                    {
                        if (FileStat.st_mode & S_IXUSR)
                        {
                            fileNames[numFiles]->filetype = 2;
                        }
                        else
                        {
                            fileNames[numFiles]->filetype = 0;
                        }
                    }
                    numFiles++;
                }
            }
            closedir(DirectoryName);
            qsort(fileNames, numFiles, sizeof(struct FileStruct *), compareStrings);
            for (int i = 0; i < numFiles; i++)
            {
                if (fileNames[i]->filetype == 2)
                {
                    printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET, fileNames[i]->FileName);
                }
                else if (fileNames[i]->filetype == 1)
                {
                    printf(ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, fileNames[i]->FileName);
                }
                else
                {
                    printf(ANSI_COLOR_WHITE "%s\n" ANSI_COLOR_RESET, fileNames[i]->FileName);
                }
                free(fileNames[i]);
            }
            free(fileNames);
        }
        else if (lflag == 1)
        {
            int maxFiles = 100;
            int numFiles = 0;
            struct FileDetails **fileNames = (struct FileDetails **)malloc(maxFiles * sizeof(struct FileDetails *));
            struct dirent *entry;
            while ((entry = readdir(DirectoryName)) != NULL)
            {
                if (numFiles >= maxFiles)
                {
                    maxFiles *= 2;
                    fileNames = (struct FileDetails **)realloc(fileNames, maxFiles * sizeof(struct FileDetails *));
                }
                if ((aflag == 1) || (aflag == 0 && entry->d_name[0] != '.'))
                {
                    fileNames[numFiles] = (struct FileDetails *)malloc(sizeof(struct FileDetails));
                    fileNames[numFiles]->name = strdup(entry->d_name);
                    struct stat FileStat;
                    stat(entry->d_name, &FileStat);
                    struct passwd *pwd = getpwuid(FileStat.st_uid);
                    struct group *grp = getgrgid(FileStat.st_gid);
                    strcpy(fileNames[numFiles]->time, entry->d_name);
                    mode_to_string(FileStat.st_mode, fileNames[numFiles]->permissions);
                    fileNames[numFiles]->nlink = FileStat.st_nlink;
                    strncpy(fileNames[numFiles]->owner, pwd->pw_name, sizeof(fileNames[numFiles]->owner) - 1);
                    fileNames[numFiles]->owner[sizeof(fileNames[numFiles]->owner) - 1] = '\0';
                    strncpy(fileNames[numFiles]->group, grp->gr_name, sizeof(fileNames[numFiles]->group) - 1);
                    fileNames[numFiles]->group[sizeof(fileNames[numFiles]->group) - 1] = '\0';
                    fileNames[numFiles]->size = FileStat.st_size;
                    strftime(fileNames[numFiles]->time, sizeof(fileNames[numFiles]->time), "%b %d %H:%M", localtime(&FileStat.st_mtime));
                    if (S_ISDIR(FileStat.st_mode))
                    {
                        fileNames[numFiles]->filetype = 1;
                    }
                    else if (S_ISREG(FileStat.st_mode))
                    {
                        if (FileStat.st_mode & S_IXUSR)
                        {
                            fileNames[numFiles]->filetype = 2;
                        }
                        else
                        {
                            fileNames[numFiles]->filetype = 0;
                        }
                    }
                    numFiles++;
                }
            }
            qsort(fileNames, numFiles, sizeof(struct FileDetails *), compareStrings1);
            closedir(DirectoryName);
            for (int i = 0; i < numFiles; i++)
            {
                if (fileNames[i]->filetype == 2)
                {
                    printf("%s %2lu %-8s %-8s %8lld %s " ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET, fileNames[i]->permissions,
                           fileNames[i]->nlink,
                           fileNames[i]->owner,
                           fileNames[i]->group,
                           fileNames[i]->size,
                           fileNames[i]->time, fileNames[i]->name);
                }
                else if (fileNames[i]->filetype == 1)
                {
                    printf("%s %2lu %-8s %-8s %8lld %s " ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, fileNames[i]->permissions,
                           fileNames[i]->nlink,
                           fileNames[i]->owner,
                           fileNames[i]->group,
                           fileNames[i]->size,
                           fileNames[i]->time, fileNames[i]->name);
                }
                else
                {
                    printf("%s %2lu %-8s %-8s %8lld %s " ANSI_COLOR_WHITE "%s\n" ANSI_COLOR_RESET, fileNames[i]->permissions,
                           fileNames[i]->nlink,
                           fileNames[i]->owner,
                           fileNames[i]->group,
                           fileNames[i]->size,
                           fileNames[i]->time, fileNames[i]->name);
                }
            }
        }
    }
}

#include "headers.h"

void CheckBackGrounds()
{
    // for (int i = 0; i < BACKGROUNDCOUNT; i++)
    // {
    //     if (Array[i].emptyflag == 0)
    //     {
    //         int status;
    //         int result = waitpid(Array[i].processid, &status, WNOHANG);
    //         if (result != 0)
    //         {
    //             if (WIFEXITED(status))
    //             {
    //                 if (WEXITSTATUS(status) == 0)
    //                 {
    //                     printf("%s exited normally (%d) \n", Array[i].Command, Array[i].processid);
    //                 }
    //                 else
    //                 {
    //                     printf("%s exited abnormally (%d) \n", Array[i].Command, Array[i].processid);
    //                 }
    //                 Array[i].emptyflag = 1;
    //             }
    //             else
    //             {
    //                 printf("%s exited abnormally (%d) \n", Array[i].Command, Array[i].processid);
    //                 Array[i].emptyflag = 1;
    //             }
    //         }
    //     }
    // }
    BackProcess Dupe = Array;
    BackProcess Prev = NULL;
    while (Dupe != NULL)
    {
        int status;
        int result = waitpid(Dupe->processid, &status, WNOHANG);
        int flag = 0;
        if (result != 0)
        {
            flag++;
            if (WIFEXITED(status))
            {
                if (WEXITSTATUS(status) == 0)
                {
                    printf("%s exited normally (%d) \n", Dupe->Command, Dupe->processid);
                }
                else
                {
                    printf("%s exited abnormally (%d) \n", Dupe->Command, Dupe->processid);
                }
            }
            else
            {
                printf("%s exited abnormally (%d) \n", Dupe->Command, Dupe->processid);
            }
        }
        if (flag != 0)
        {
            if (Prev != NULL)
            {
                BackProcess Clearer = Dupe;
                Prev->Nextstrawberry = Dupe->Nextstrawberry;
                Dupe = Prev->Nextstrawberry;
                free(Clearer);
            }
            else
            {
                BackProcess Clearer = Dupe;
                Array = Dupe->Nextstrawberry;
                Dupe = Array;
                free(Clearer);
            }
        }
        if (flag == 0)
        {
            Prev = Dupe;
            Dupe = Dupe->Nextstrawberry;
        }
    }
}
void bg(char **ARGV)
{
    pid_t processid = atoi(ARGV[1]);
    int glag = 0;
    BackProcess Dupe = Array;
    while (Dupe != NULL)
    {
        if (Dupe->processid == processid)
        {
            kill(processid, SIGCONT);
            glag++;
            break;
        }
        // for (int i = 0; i < BACKGROUNDCOUNT; i++)
        // {
        // if (Array[i].emptyflag == 0)
        // {
        //     if (Array[i].processid = processid)
        //     {
        //         kill(processid, SIGCONT);
        //         glag++;
        //         break;
        //     }
        // }
        // }
    }
    if (glag == 0)
    {
        printf("No such process found\n");
    }
}
// void fg(char **ARGV)
// {
//     pid_t processid = atoi(ARGV[1]);
//     int glag = 0;
//     for (int i = 0; i < BACKGROUNDCOUNT; i++)
//     {
//         if (Array[i].emptyflag == 0)
//         {
//             if (Array[i].processid == processid)
//             {
//                 glag++;
//                 int status;
//                 Foreground = processid;
//                 kill(processid, SIGCONT);
//                 waitpid(processid, &status, __W_CONTINUED);
//                 break;
//             }
//         }
//     }
//     if (glag == 0)
//     {
//         printf("No such process found\n");
//     }
// }
void fg(char **ARGV)
{
    pid_t background_pid = atoi(ARGV[1]);
    BackProcess Dupe = Array;
    BackProcess Prev = NULL;
    int flag = 0;
    while (Dupe != NULL)
    {
        if (Dupe->processid == background_pid)
        {
            flag++;
            int status;
            if (kill(background_pid, SIGSTOP) == -1)
            {
                perror("kill");
                exit(EXIT_FAILURE);
            }
            if (tcsetpgrp(STDIN_FILENO, background_pid) == -1)
            {
                perror("tcsetpgrp");
                exit(EXIT_FAILURE);
            }
            if (kill(background_pid, SIGCONT) == -1)
            {
                perror("kill");
                exit(EXIT_FAILURE);
            }
            // Foreground = background_pid;
            // printf("%d : Fg\n", Foreground);
            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);
            // Wait for the background process to finish.
            if (waitpid(background_pid, &status, WUNTRACED) == -1)
            {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }

            // Restore control to the shell (parent process).
            if (tcsetpgrp(STDIN_FILENO, getpgrp()) == -1)
            {
                perror("tcsetpgrp");
                exit(EXIT_FAILURE);
            }
            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);
            break;
        }
        Dupe = Dupe->Nextstrawberry;
    }
    if (flag == 0)
    {
        printf("No such process found\n");
    }
    else
    {
        if (Prev != NULL)
        {
            BackProcess Clearer = Dupe;
            Prev->Nextstrawberry = Dupe->Nextstrawberry;
            Dupe = Prev->Nextstrawberry;
            free(Clearer);
        }
        else
        {
            BackProcess Clearer = Dupe;
            Array = Dupe->Nextstrawberry;
            Dupe = Array;
            free(Clearer);
        }
    }
    return;
}
// void CreatBackArray()
// {
//     for (int i = 0; i < BACKGROUNDCOUNT; i++)
//     {
//         Array[i].emptyflag = 1;
//     }
// }
void BackGround(char *INPUT)
{
    char **ARGV = tokens(INPUT);
    pid_t pid = fork();
    setpgid(0, 0);
    if (pid == 0)
    {
        if (execvp(ARGV[0], ARGV) == -1)
        {
            perror("Error in executing the Command");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        printf("%d\n", pid);
        // int k = -1;
        // for (int i = 0; i < BACKGROUNDCOUNT; i++)
        // {
        //     if (Array[i].emptyflag == 1)
        //     {
        //         k = i;
        //         break;
        //     }
        // }
        // if (k == -1)
        // {
        //     printf("Error: The maximum number of background processes has been exceeded.\n");
        //     return;
        // }
        // else
        // {
        //     Array[k].emptyflag = 0;
        //     Array[k].processid = pid;
        //     strcpy(Array[k].Command, ARGV[0]);
        //     Array[k].Command[0] = toupper(Array[k].Command[0]);
        // }
        BackProcess New = (BackProcess)malloc(sizeof(struct BackProcesses));
        New->processid = pid;
        strcpy(New->Command, ARGV[0]);
        New->Command[0] = toupper(New->Command[0]);
        if (Array == NULL)
        {
            Array = New;
        }
        else
        {
            BackProcess Dupe = Array;
            if (Dupe->processid > New->processid)
            {
                New->Nextstrawberry = Dupe;
                Array = New;
            }
            else
            {
                while (Dupe->Nextstrawberry != NULL && Dupe->Nextstrawberry->processid < New->processid)
                {
                    Dupe = Dupe->Nextstrawberry;
                }
                if (Dupe->Nextstrawberry == NULL)
                {
                    Dupe->Nextstrawberry = New;
                    New->Nextstrawberry = NULL;
                }
                else
                {
                    New->Nextstrawberry = Dupe->Nextstrawberry;
                    Dupe->Nextstrawberry = New;
                }
            }
        }
    }
}
void KillAll()
{
    BackProcess Dupe = Array;
    while (Dupe != NULL)
    {
        // if (Array[i].emptyflag == 0)
        // {
        //     kill(Array[i].processid, 2);
        //     Array[i].emptyflag = 1;
        // }
        kill(Dupe->processid, SIGINT);
        BackProcess Clearer = Dupe;
        Dupe = Dupe->Nextstrawberry;
        free(Clearer);
    }
    printf("\n");
    exit(EXIT_SUCCESS);
}

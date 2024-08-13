#include "headers.h"

struct strawberries
{
    pid_t processid;
    char status[15];
    char Command[256];
    struct strawberries *Nextstrawberry;
};
typedef struct strawberries *Strawberry;
void Activities()
{
    // Strawberry Start = NULL;
    // for (int i = 0; i < BACKGROUNDCOUNT; i++)
    // {
    //     if (Array[i].emptyflag == 0)
    //     {
    //         Strawberry New = (Strawberry)malloc(sizeof(struct strawberries));
    //         char statfile[256];
    //         snprintf(statfile, 256, "/proc/%d/stat", Array[i].processid);
    //         FILE *Stat_file = fopen(statfile, "r");
    //         if (Stat_file != NULL)
    //         {
    //             char stat_data[256];
    //             fgets(stat_data, 256, Stat_file);
    //             fclose(Stat_file);
    //             int extracted_pid;
    //             char comm[256], state;
    //             int ppid, pgrp, session, tty_nr, tpgid;
    //             sscanf(stat_data, "%d %s %c %d %d %d %d %d", &extracted_pid, comm, &state, &ppid, &pgrp, &session, &tty_nr, &tpgid);
    //             if (state != 'T')
    //             {
    //                 New->processid = Array[i].processid;
    //                 New->Nextstrawberry = NULL;
    //                 strcpy(New->status, "Running");
    //                 strcpy(New->Command, Array[i].Command);
    //             }
    //             else
    //             {
    //                 New->processid = Array[i].processid;
    //                 New->Nextstrawberry = NULL;
    //                 strcpy(New->status, "Stopped");
    //                 strcpy(New->Command, Array[i].Command);
    //             }
    //             if (Start == NULL)
    //             {
    //                 Start = New;
    //             }
    //             else
    //             {
    //                 Strawberry Dupe = Start;
    //                 if (Dupe->processid > New->processid)
    //                 {
    //                     New->Nextstrawberry = Dupe;
    //                     Start = New;
    //                 }
    //                 while (Dupe->Nextstrawberry != NULL && Dupe->Nextstrawberry->processid < New->processid)
    //                 {
    //                     Dupe = Dupe->Nextstrawberry;
    //                 }
    //                 if (Dupe->Nextstrawberry == NULL)
    //                 {
    //                     Dupe->Nextstrawberry = New;
    //                     New->Nextstrawberry = NULL;
    //                 }
    //                 else
    //                 {
    //                     New->Nextstrawberry = Dupe->Nextstrawberry;
    //                     Dupe->Nextstrawberry = New;
    //                 }
    //             }
    //         }
    //         else
    //         {
    //             Array[i].emptyflag = 1;
    //         }
    //     }
    // }
    // while (Start != NULL)
    // {
    //     printf("%d : %s - %s \n", Start->processid, Start->Command, Start->status);
    //     Strawberry Greater = Start;
    //     Start = Start->Nextstrawberry;
    //     free(Greater);
    // }
    BackProcess Dupe = Array;
    while (Dupe != NULL)
    {
        char statfile[256];
        snprintf(statfile, 256, "/proc/%d/stat", Dupe->processid);
        FILE *Stat_file = fopen(statfile, "r");
        if (Stat_file != NULL)
        {
            char stat_data[256];
            fgets(stat_data, 256, Stat_file);
            fclose(Stat_file);
            int extracted_pid;
            char comm[256], state;
            int ppid, pgrp, session, tty_nr, tpgid;
            sscanf(stat_data, "%d %s %c %d %d %d %d %d", &extracted_pid, comm, &state, &ppid, &pgrp, &session, &tty_nr, &tpgid);
            if (state != 'T')
            {
                printf("%d : %s - Running \n", Dupe->processid, Dupe->Command);
            }
            else
            {
                printf("%d : %s - Stopped \n", Dupe->processid, Dupe->Command);
            }
        }
        Dupe = Dupe->Nextstrawberry;
    }
}

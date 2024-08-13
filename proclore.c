#include "headers.h"

void proclore(char **Command)
{
    int i = 1;
    int flag = 0;
    while (Command[i] != NULL)
    {

        if (strcmp(Command[i], "\n"))
        {
            flag++;
            int processid = atoi(Command[i]);
            RealProclore(processid);
        }
        i++;
    }
    if (flag == 0)
    {
        RealProclore(getpid());
    }
    return;
}
void RealProclore(int PROCID)
{
    char stat_path[256];
    char status_path[256];
    snprintf(stat_path, 256, "/proc/%d/stat", PROCID);
    snprintf(status_path, 256, "/proc/%d/status", PROCID);
    pid_t pgid = getpgid(PROCID);
    pid_t foreground_pgid = tcgetpgrp(STDIN_FILENO);
    int foreflag = 0;
    if (pgid == foreground_pgid)
    {
        foreflag++;
    }
    FILE *stat_file = fopen(stat_path, "r");
    if (stat_file == NULL)
    {
        perror("Failed to open stat file");
        return;
    }
    char stat_data[2048];
    if (fgets(stat_data, sizeof(stat_data), stat_file) == NULL)
    {
        perror("Failed to read stat file");
        fclose(stat_file);
        return;
    }
    fclose(stat_file);
    FILE *status_file = fopen(status_path, "r");
    if (status_file == NULL)
    {
        perror("Failed to open status file");
        return;
    }
    char line[256];
    char vm_size[256] = "";
    while (fgets(line, sizeof(line), status_file) != NULL)
    {
        if (strstr(line, "VmSize:") != NULL)
        {
            sscanf(line, "VmSize: %s", vm_size);
            break;
        }
    }
    fclose(status_file);
    int extracted_pid;
    char comm[256], state;
    int ppid, pgrp, session, tty_nr, tpgid;

    sscanf(stat_data, "%d %s %c %d %d %d %d %d", &extracted_pid, comm, &state, &ppid, &pgrp, &session, &tty_nr, &tpgid);
    char exe_path[2048];
    snprintf(exe_path, sizeof(exe_path), "/proc/%d/exe", PROCID);
    readlink(exe_path, exe_path, sizeof(exe_path));
    printf("pid : %d\n", PROCID);
    if (foreflag == 1 && state != 'Z')
    {
        printf("process status : %c+\n", state);
    }
    else
    {
        printf("process status : %c\n", state);
    }
    printf("Process Group : %d\n", pgrp);
    printf("Virtual Memory Size: %s\n", vm_size);
    printf("executable Path: %s\n", exe_path);
    return;
}
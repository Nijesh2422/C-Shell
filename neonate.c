#include "headers.h"

void die(const char *s)
{
    perror(s);
    exit(1);
}

struct termios orig_termios;

void disableRawMode()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}
void enableRawMode()
{
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}

void Neonate(char **ARGV)
{
    int time = atoi(ARGV[2]);
    enableRawMode();

    int pad = -1;
    char loadavg[256];
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return;
    }
    else if (pid == 0)
    {
        while (1)
        {
            int loadavg_fd = open("/proc/loadavg", O_RDONLY);
            if (loadavg_fd < 0)
            {
                perror("open /proc/loadavg");
                return;
            }
            ssize_t bytes_read = read(loadavg_fd, loadavg, sizeof(loadavg) - 1);
            close(loadavg_fd);

            if (bytes_read < 0)
            {
                perror("read /proc/loadavg");
                return;
            }
            double last_pid = 0;
            sscanf(loadavg, "%*s %*s %*s %*s %lf", &last_pid);
            if (last_pid > 0)
            {
                if (pid != (int)last_pid)
                {
                    pid = (int)last_pid;
                    printf("%d\n", pid);
                }
            }
            sleep(time);
        }
    }
    else
    {
        char c;
        if (read(STDIN_FILENO, &c, 1) == 1 && c == 'x')
        {
            kill(pid, SIGKILL);
        }
    }
    disableRawMode();
    return;
}
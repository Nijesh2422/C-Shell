#ifndef HEADERS_H_
#define HEADERS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include "prompt.h"
#include "warp.h"
#include "peek.h"
#include "execute.h"
#include "pastevents.h"
#include "proclore.h"
#include <sys/types.h>
#include <sys/wait.h>
#include "tokens.h"
#include "seek.h"
#include "redirection.h"
#include "semicolontokens.h"
#include <fcntl.h>
#include <sys/time.h>
#include <math.h>
#include "background.h"
#include "piping.h"
#include "pipetoken.h"
#include "activities.h"
#include "ping.h"
#include <signal.h>
#include "signals.h"
#include "neonate.h"
#include <termios.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "iman.h"
#define MAX_BUFFER_SIZE 100000
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_WHITE "\x1b[37m"
#define ANSI_COLOR_RESET "\x1b[0m"
// #define BACKGROUNDCOUNT 100
extern int PASTEVENTSFLAG;
extern int matchesfound;
extern char prevCommand[256];
extern double time_elapsed;
extern int somthn;
// typedef struct BackProcesses
// {
//     char Command[256];
//     pid_t processid;
//     int emptyflag;
// } BackProcess;

struct BackProcesses
{
    char Command[256];
    pid_t processid;
    struct BackProcesses *Nextstrawberry;
};
typedef struct BackProcesses *BackProcess;

extern pid_t Foreground;
extern char Dofrramingo[256];
extern BackProcess Array;

#endif
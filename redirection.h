#ifndef __REDIRECTION_H
#define __REDIRECTION_H

int redirect(char **INPUT);
void GoDescs(int *INPUTFD, int *OUTPUTFD);
void ResetDescs(int *INPUTFD, int *OUTPUTFD);

#endif
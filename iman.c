#include "headers.h"
void Iman(char **ARGV)
{
    struct hostent *server;
    struct sockaddr_in server_addr;
    int sockfd;
    server = gethostbyname("man.he.net");
    if (server == NULL)
    {
        perror("Error: DNS resolution failed");
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error: Failed to open socket");
    }
    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);
    bcopy((char *)server->h_addr_list[0], (char *)&server_addr.sin_addr.s_addr, server->h_length);
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Error: Failed to connect to server");
    }
    char request[MAX_BUFFER_SIZE];
    snprintf(request, sizeof(request), "GET /?topic=%s&section=all HTTP/1.1\r\nHost: man.he.net\r\n\r\n", ARGV[1]);
    if (write(sockfd, request, strlen(request)) < 0)
    {
        perror("Error: Failed to send GET request");
    }
    char buffer[MAX_BUFFER_SIZE];
    int n;
    int yoflag = 0;
    int glag = 0;
    while ((n = read(sockfd, buffer, sizeof(buffer))) > 0)
    {
        if (yoflag)
        {
            break;
        }
        if (glag == 0)
        {
            char *string = strstr(buffer, "No matches for");
            if (string != NULL)
            {
                printf("ERROR\n\tNo such command\n");
                return;
            }
        }
        int readflag = 0;
        int i = 0;
        while (buffer[i] != '\0')
        {
            if (readflag > 0)
            {
                while (buffer[i] != '<')
                {
                    printf("%c", buffer[i]);
                    i++;
                }
                readflag--;
            }
            else if (buffer[i] == '>')
            {
                readflag++;
                if (buffer[i - 1] == 'l' && buffer[i - 2] == 'm' && buffer[i - 3] == 't' && buffer[i - 4] == 'h' && buffer[i - 5] == '/' && buffer[i - 6] == '<')
                {
                    yoflag++;
                    break;
                }
            }
            i++;
        }
    }
    close(sockfd);
}
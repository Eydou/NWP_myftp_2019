/*
** EPITECH PROJECT, 2020
** NWP
** File description:
** server
*/

#include "server.h"
#include <sys/select.h>

int is_space(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] != ' ')
            return -1;
    return 0;
}

static s_serv_t *init_server(int sockfd, int max_sd, fd_set fds, s_serv_t *serv)
{
    serv = malloc(sizeof(s_serv_t));
    serv->fds = fds;
    serv->max_sd = max_sd;
    serv->sockfd = sockfd;

    return serv;
}

static int is_wait_server(int s_sockfd, char *path, struct sockaddr_in s_addr)
{
    client_serv_t s_client[MAX_CLIENT];
    fd_set fds;
    int max_sd = s_sockfd;
    s_serv_t *serv;

    for (int i = 0; i < MAX_CLIENT; i++) {
        s_client[i].sockfd = 0;
        s_client[i].path = path;
        s_client[i].backup = path;
    }
    if ((listen(s_sockfd, MAX_CLIENT)) != 0) {
        perror("listen()");
        return -1;
    }
    puts("waiting clients...");
    serv = init_server(s_sockfd, max_sd, fds, serv);
    loop_client(s_client, serv);
    close(s_sockfd);
    return 0;
}

int start_server(int port, char *path)
{
    struct sockaddr_in s_addr = {0};
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1) {
        perror("socket(): ");
        return -1;
    }
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(port);
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
    &s_addr, sizeof(int)) == -1) {
        perror("setsockopt()");
        return -1;
    }
    if (bind(sockfd, (struct sockaddr *) &s_addr, sizeof(s_addr)) == -1) {
        perror("bind()");
        return -1;
    }
    return is_wait_server(sockfd, path, s_addr);
}
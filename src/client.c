/*
** EPITECH PROJECT, 2020
** NWP
** File description:
** client_handler
*/

#include "server.h"
#include <sys/select.h>

static void clean_client(client_serv_t client[MAX_CLIENT], int id, int i)
{
    c_message(client[id].sockfd, "221 Goodbye.");
    free(client[id].message);
    client[id].message = NULL;
    close(client[id].sockfd);
    client[id].sockfd = 0;
    for (int nb = 0; nb < i; nb++)
        free(client[id].command[nb]);
    free(client[id].command);
    client[id].login = false;
    client[id].message = false;
    client[id].path = NULL;
    client[id].backup = NULL;
    client[id].copy_sockfd = 0;
}

static void start_client(client_serv_t client[MAX_CLIENT], int id)
{
    int i = 0;
    char **command = NULL;
    client[id].message = NULL;
    client[id].message = get_next_line(client[id].sockfd);
    client[id].message[strlen(client[id].message) - 1] = '\0';
    client[id].command = my_str_to_wordarry(client[id].message,
    command);
    printf("%s\n", client[id].path);
    for (;client[id].command[i] != NULL; i++);
    if (!strcmp(client[id].message, "USER") && client[id].enter != true
    && strcmp(client[id].message, "") != 0) {
        c_message(client[id].sockfd, "530 Permission denied.");
        return;
    }
    handling_command_client(client, id, i);
    if (!strcmp(client[id].message, "QUIT")) {
        clean_client(client, id, i);
        return;
    }
    free(client[id].message);
}

static void fill_client(client_serv_t s_client[MAX_CLIENT], s_serv_t *serv)
{
    int new_socket = 0;
    struct sockaddr_in client = {0};
    int client_size = sizeof(client);

    if (FD_ISSET(serv->sockfd, &serv->readfds)) {
        if ((new_socket = accept(serv->sockfd,
        (struct sockaddr *)&client, (socklen_t *)&client_size)) == -1) {
            perror("accept");
            exit(84);
        }
        for (int i = 0; i < MAX_CLIENT; i++) {
            s_client[i].ip = client.sin_addr.s_addr;
            if (s_client[i].sockfd == 0) {
                s_client[i].sockfd = new_socket;
                break;
            }
        }
    }
    c_message(new_socket, "220 Welcome to my server :)");
}

static void init_client(client_serv_t s_client[MAX_CLIENT], s_serv_t *serv)
{
    FD_ZERO(&serv->readfds);
    FD_SET(serv->sockfd, &serv->readfds);
    serv->max_sd = serv->sockfd;
    for (int i = 0 ; i < MAX_CLIENT ; i++) {
        if (s_client[i].sockfd > 0)
            FD_SET(s_client[i].sockfd, &serv->readfds);
        if (s_client[i].sockfd > serv->max_sd)
            serv->max_sd = s_client[i].sockfd;
    }
    if (select(serv->max_sd + 1 , &serv->readfds , NULL , NULL , NULL) == -1) {
        perror("select()");
        exit(84);
    }
}

int loop_client(client_serv_t s_client[MAX_CLIENT], s_serv_t *serv)
{
    for (;;) {
        init_client(s_client, serv);
        fill_client(s_client, serv);
        for (int i = 0; i < MAX_CLIENT; i++) {
            if (FD_ISSET(s_client[i].sockfd, &serv->readfds)) {
                start_client(s_client, i);
            }
        }
    }
    return 0;
}

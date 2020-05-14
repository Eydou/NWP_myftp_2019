/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** command
*/

#include "server.h"

void is_help(client_serv_t client[MAX_CLIENT], int id, int len)
{
    c_message(client[id].sockfd, "214 help message.");
}

void is_noop(client_serv_t client[MAX_CLIENT], int id, int len)
{
    c_message(client[id].sockfd, "200 Nothing.");
}

void is_pwd(client_serv_t client[MAX_CLIENT], int id, int len)
{
    dprintf(client[id].sockfd, "257 %s\n", client[id].path);
}

void is_delete(client_serv_t client[MAX_CLIENT], int id, int len)
{
    if (len > 1) {
        if (remove(client[id].command[1]) == -1)
            c_message(client[id].sockfd, "550 error delete.");
        else
            c_message(client[id].sockfd, "250 Sucessful delete.");
    } else
        c_message(client[id].sockfd, "550 error delete.");
}

void is_cwd(client_serv_t client[MAX_CLIENT], int id, int len)
{
    char *backup =  malloc(1024);
    char *real_path = malloc(1024);

    if (len == 1) {
        c_message(client[id].sockfd, "550 cwd ko.");
        return;
    }
    backup = strcat(backup, client[id].path);
    backup = strcat(backup, "/");
    backup = strcat(backup, client[id].command[1]);
    if ((chdir(realpath(backup, real_path))) != -1) {
        c_message(client[id].sockfd, "250 cwd ok.");
        client[id].path = real_path;
    } else {
        c_message(client[id].sockfd, "550 cwd ko.");
        client[id].path = client[id].backup;
    }
    free(backup);
    free(real_path);
}
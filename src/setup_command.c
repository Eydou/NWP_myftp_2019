/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** setup_command
*/

#include "server.h"

void is_psv(client_serv_t client[MAX_CLIENT], int id, int len)
{
    struct sockaddr_in addr;
    struct in_addr ip_addr;

    if ((client[id].copy_sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        c_message(client[id].sockfd, "550 pasv ko.");
        return;
    }
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = client[id].ip;
    addr.sin_port = 0;
    if (bind(client[id].copy_sockfd, (struct sockaddr *)&addr, sizeof(addr))
    == -1 || listen(client[id].copy_sockfd, MAX_CLIENT) == -1) {
        c_message(client[id].sockfd, "550 pasv ko.");
        return;
    }
    ip_addr.s_addr = client[id].ip;
    dprintf(client[id].sockfd, "227 pasv ok %s.\n", inet_ntoa(ip_addr));
    client[id].passive = true;
}

void is_cdup(client_serv_t client[MAX_CLIENT], int id, int len)
{
    char *backup =  malloc(1024);
    char *real_path = malloc(1024);

    backup = strcat(backup, client[id].path);
    backup = strcat(backup, "/");
    backup = strcat(backup, "../");

    if ((chdir(realpath(backup, real_path))) != -1) {
        c_message(client[id].sockfd, "200 cdup ok.");
        client[id].path = real_path;
    } else {
        c_message(client[id].sockfd, "550 cwd ko.");
        client[id].path = client[id].backup;
    }
    free(backup);
    free(real_path);
}
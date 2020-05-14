/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** command_client
*/

#include "server.h"

static command _command[7] = {&is_help, &is_noop, &is_pwd,
&is_delete, &is_cwd, &is_psv, &is_cdup};

static void is_command_client(client_serv_t client[MAX_CLIENT], int id,
int len)
{
    char *command_first[] = {"HELP", "NOOP", "PWD", "DELE", "CWD", "PASV",
    "CDUP"};

    if (!strcmp(client[id].command[0], "USER")) {
        c_message(client[id].sockfd, "530 Can't change from guest user.");
        return;
    }
    for (int i = 0; i != 7; i++) {
        if (!strcmp(client[id].command[0], command_first[i])) {
            _command[i](client, id, len);
            return;
        }
    }
    if ((strcmp(client[id].message, "") != 0 &&
    is_space(client[id].message) == -1) &&
    strcmp(client[id].command[0], "PASS") != 0)
        c_message(client[id].sockfd, "500 Commande not found.");
}

static int login_client(client_serv_t client[MAX_CLIENT], int id,
int len)
{
    if (len > 1) {
        if (!strcmp(client[id].command[0], "USER")) {
            client[id].user = client[id].command[1];
            len > 2 && client[id].enter != true
            ? c_message(client[id].sockfd, "503 Login with USER first.") : 0;
            len > 1 && client[id].enter != true && len < 3 ?
            c_message(client[id].sockfd, "331 Please specify the pass") : 0;
            if (!strcmp(client[id].user, "Anonymous"))
                client[id].login = true;
            return 1;
        }
    }
    if (len >= 1 && !strcmp(client[id].command[0], "PASS")
    && client[id].login == true) {
        c_message(client[id].sockfd, "230 Login successful.");
        client[id].enter = true;
        return 1;
    }
    return 0;
}

void handling_command_client(client_serv_t client[MAX_CLIENT], int id,
int len)
{
    if ((login_client(client, id, len) == 1) && client[id].enter != true)
        return;
    if (len >= 1 && !strcmp(client[id].command[0], "PASS")
    && client[id].login == false) {
        c_message(client[id].sockfd, "530 Login incorrect.");
        return;
    }
    if (client[id].enter == true)
        is_command_client(client, id, len);
    else if (strcmp(client[id].message, "") != 0 &&
    is_space(client[id].message) == -1)
        c_message(client[id].sockfd, "530 Please login with USER and PASS.");
}
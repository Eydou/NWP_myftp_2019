/*
** EPITECH PROJECT, 2020
** NWP
** File description:
** server
*/

#ifndef SERVER_H_
#define SERVER_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#include <string.h>
#include <stdbool.h>
#define closesocket(s) close(s)
#define MAX_CLIENT 10

typedef struct client_serv_s
{
    int sockfd;
    int copy_sockfd;
    char **command;
    char *message;
    char *user;
    ssize_t ip;
    char *path;
    char *backup;
    bool login;
    bool enter;
    bool passive;
} client_serv_t;

typedef struct s_serv_s
{
    int sockfd;
    fd_set fds;
    int max_sd;
    fd_set readfds;
} s_serv_t;

typedef void (*command)(client_serv_t client[MAX_CLIENT], int, int);

static const void c_message(int socket, char *str)
{
    dprintf(socket, "%s\r\n", str);
}

char *get_next_line(const int fd);
int is_space(char *str);

int start_server(int, char *);
int loop_client(client_serv_t s_client[MAX_CLIENT], s_serv_t *serv);
char **my_str_to_wordarry(char *str, char **path);
void handling_command_client(client_serv_t client[MAX_CLIENT], int id,
int len);

void is_help(client_serv_t client[MAX_CLIENT], int id, int len);
void is_noop(client_serv_t client[MAX_CLIENT], int id, int len);
void is_syst(client_serv_t client[MAX_CLIENT], int id, int len);
void is_pwd(client_serv_t client[MAX_CLIENT], int id, int len);
void is_delete(client_serv_t client[MAX_CLIENT], int id, int len);
void is_cwd(client_serv_t client[MAX_CLIENT], int id, int len);
void is_psv(client_serv_t client[MAX_CLIENT], int id, int len);
void is_cdup(client_serv_t client[MAX_CLIENT], int id, int len);

#endif /* !SERVER_H_ */

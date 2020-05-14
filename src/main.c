/*
** EPITECH PROJECT, 2020
** NWP
** File description:
** main
*/

#include "server.h"
#include <ctype.h>

void help(void)
{
    printf("USAGE: ./myftp port path\n");
    printf("\tport is the port number on which the server socket listens\n");
    printf("\tpath is the path to the home directory for the Anonymous user\n");
    return;
}

int verify_nb(char * string)
{
    for (size_t i = 0; i < strlen(string); i++) {
        if (!isdigit(*(string+i)))
            return -1;
    }
    return 0;
}

int main(size_t ac, char **av)
{
    char buffer[1000 + 1];

    if (ac != 3) {
        help();
        return 84;
    }
    if (verify_nb(av[1]) != 0)
        return (84);
    realpath(av[2], buffer);
    if (chdir(buffer) != 0)
        return (perror(av[2]), 84);
    else if (atoi(av[1]) > 0 && atoi(av[1]) < 65535)
    {
        if (start_server(atoi(av[1]), buffer) != 0)
            return 84;
    }
    return 0;
}

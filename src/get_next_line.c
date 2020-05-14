/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** get_next_line
*/

#include "server.h"

static char *my_calloc(int size)
{
    char *res = malloc(size);

    if (res == NULL)
        return (NULL);
    for (int i = 0; i != size; i++)
        res[i] = '\0';
    return (res);
}

static int init_str(char **str, char **buffer, int i)
{
    i = 0;
    if ((*str = my_calloc(sizeof(char) * (100 + 1))) == NULL)
        return -1;
    for (;**buffer != 0 && (!i || *(*buffer - 1) != '\n'); i++,
    (*buffer)++)
        (*str)[i] = **buffer;
    return i;
}

static char *init_buffer(char *buffer, const int fd)
{
    int val = 0;

    if ((buffer = my_calloc(sizeof(char) * (100 + 1))) == NULL)
        return NULL;
    if ((val = read(fd, buffer, 100)) == -1)
        return NULL;
    buffer[val] = '\0';
    return buffer;
}

char *get_next_line(const int fd)
{
    char *str;
    int nb;
    char *buffer = init_buffer(buffer, fd);

    if (buffer == NULL || !buffer[0])
        return NULL;
    if ((nb = init_str(&str, &buffer, nb)) == -1)
        return NULL;
    str[nb] = '\0';
    if (nb != 0 && str[nb - 1] == '\n')
        str[nb - 1] = '\0';
    else
        str = strcat(str, get_next_line(fd));
    return str;
}
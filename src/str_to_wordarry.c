/*
** EPITECH PROJECT, 2019
** str_to_wordarr.
** File description:
** str_to_wordarr.
*/

#include "server.h"

char *my_calloc(int size)
{
    char *res = malloc(size);

    if (res == NULL)
        return (NULL);
    for (int i = 0; i != size; i++)
        res[i] = '\0';
    return (res);
}

int get_space(char *str)
{
    int space = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ' ' || str[i] == ':')
            space++;
    }
    space++;
    return (space);
}

char **setup_str_to_wordarry(char *str, char **path, int line, int j)
{
    int spaces = get_space(str);

    path = malloc(sizeof(char *) * spaces + 100);
    for (int i = 0; i <= spaces ; i++)
        path[i] = my_calloc(sizeof(char) * strlen(str) + 100);
    for (int z = 0; str[j] != '\0'; z++) {
        path[line][z] = str[j];
        j++;
        if (str[j] == '=') {
            z = -1;
            j++;
        } else if (str[j] == ' ' || str[j] == ':') {
            line++;
            j++;
            z = -1;
        }
        if (str[j + 1] == '\0')
            path[line + 1] = NULL;
    }
    return (path);
}

char **my_str_to_wordarry(char *str, char **path)
{
    int line = 0;
    int j = 0;

    path = setup_str_to_wordarry(str, path, line, j);
    return (path);
}

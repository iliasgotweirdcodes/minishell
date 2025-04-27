/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:14:17 by aromani           #+#    #+#             */
/*   Updated: 2025/04/25 18:18:37 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t get_len(char *str, char sep)
{
    size_t i;
    size_t c;

    c = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == sep)
            c++;
        i++;
    }
    return (c);
}

void cd_builtins(char *path)
{
    char *pwd;

    if (access(path, F_OK) == -1)
        printf("bash: cd: %s: No such file or directory", path);
    pwd = getcwd(NULL, 0);
    if (!pwd)
        return (perror(" "));
    if (get_len(pwd) < get_len(path))
    {
        if (chdir("HOME") == -1)
            perror(" ");
    }
    else
    {
        if (chdir(path) == -1)
            perror(" ");
    }
}

/// : in parent proccess : export with args && cd && exit && unset
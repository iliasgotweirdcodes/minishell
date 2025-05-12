/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:14:35 by aromani           #+#    #+#             */
/*   Updated: 2025/05/12 18:00:28 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int unset_parser(char *key)
{
    int i;
    
    i = 0;
    while (key[i])
    {
        if (key[i] == '+' || key[i] == '=')
            return (0);
        i++;
    }
    return (1);
}
void printer(char *str1,char *key, int fd, char* str3)
{
    write(fd, str1, sizeof(str1));
    write(fd, key, sizeof(key));
    write(fd, str3, sizeof(str3));
}
int    unset_management(t_env **env, char *key, t_gc **exec)
{
    t_env *tmp;
    t_env *prev;

    if (!env || !*env || !key)
        return (0);
    if (ft_strcmp(key,"_") == 0)
        return (0);
    if (export_parser(key, exec) == 0 || unset_parser(key) == 0)
    { 
        error_printer(key, ": not a valid identifier\n", "unset: ");
        return (-1);
    }
    tmp = *env;
    prev = NULL;
    while (tmp != NULL)
    {
        if (ft_strcmp(tmp->key, key) == 0)
        {
            if (prev == NULL)
                *env = tmp->next;
            else
                prev->next = tmp->next;
            return (0);
        }
        prev = tmp;
        tmp = tmp->next;
    }
    return (0);
}

int   unset_builtins(t_env **my_env, t_command **cmd, t_gc **exec)
{
    int i;
    int status;

    status = 0;
    i = 1;
    while((*cmd)->cmd && (*cmd)->cmd[i])
    {
        if (unset_management(my_env, (*cmd)->cmd[i++], exec) == -1)
            status = 1;
    }
    return (status);
}
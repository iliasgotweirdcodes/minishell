/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:14:35 by aromani           #+#    #+#             */
/*   Updated: 2025/05/09 22:26:32 by aromani          ###   ########.fr       */
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
void    unset_management(t_env **env, char *key, t_gc **exec)
{
    t_env *tmp;
    t_env *prev;

    if (!env || !*env || !key)
        return ;
    if (export_parser(key, exec) == 0 || unset_parser(key) == 0)
    { 
        error_printer(key, ": not a valid identifier\n", "unset: ");
        return ;
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
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

int   unset_builtins(t_env **my_env, t_command **cmd, t_gc **exec)
{
    int i;

    i = 1;
    while((*cmd)->cmd && (*cmd)->cmd[i])
        unset_management(my_env, (*cmd)->cmd[i++], exec);
    return (0);
}
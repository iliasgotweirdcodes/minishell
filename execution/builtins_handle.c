/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:09:46 by aromani           #+#    #+#             */
/*   Updated: 2025/04/21 23:57:05 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void is_builtins(t_command *cmd)
{
    char *str;
    t_command *tmp;

    tmp = cmd;
    while (tmp != NULL)
    {
        if (ft_strcmp(tmp->cmd[0] ,"pwd") == 0)
        {
            str = getcwd(NULL, 0);
            if (!str)
                return (perror ("getcwd() error"), exit(1));
            ft_putstr(str);
            ft_putstr("\n");
        }
        else if (ft_strcmp(tmp->cmd[0] ,"cd") == 0)
        {
            if (chdir(tmp->cmd[1]) == -1)
                return (perror ("chdir() error"), exit(1));
        }
        tmp = tmp->next;
    }
} 
 
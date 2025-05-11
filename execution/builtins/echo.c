/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:14:22 by aromani           #+#    #+#             */
/*   Updated: 2025/05/11 21:47:58 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int is_noption(char *str)
{
    int i;

    i = 0;
    if (str[i] == '-')
        i++;
    else
        return (1);
    while (str[i])
    {
        if (str[i] != 'n')
            return (1);
        i++;
    }
    return (0);
    
}

int echo_builtind(t_command **command)
{
    int i;
    int newline_flag;
    t_command *cmd;

    newline_flag = 0;
    cmd = *command;
    i = 1;
    while (cmd->cmd[i] && is_noption(cmd->cmd[i]) == 0)
    {
        newline_flag = 1;
        i++;
    }
    while (cmd->cmd[i])
    {
        ft_putstr_fd(cmd->cmd[i], 1);
        if (cmd->cmd[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (newline_flag == 0)
        ft_putstr_fd("\n", 1);
    // if (ft_strcmp((*cmd)->cmd[1] , "-n") == 0)
    //     ft_putstr_fd((*cmd)->cmd[2], 1);
    // else
    // {
    //     ft_putstr_fd((*cmd)->cmd[1],1);
    //     ft_putstr_fd("\n",1);
    // }
    return (0);
}
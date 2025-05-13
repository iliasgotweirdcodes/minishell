/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:14:27 by aromani           #+#    #+#             */
/*   Updated: 2025/05/14 00:36:34 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int cmd_sizer(t_command *cmd)
{
    int i;

    i = 0;
    while (cmd->cmd && cmd->cmd[i])
        i++;
    return (i);
}

int exit_parser(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (1);
    while (str[i])
    {
        if (ft_isdigit(str[i]) == 0)
            return (0);
        i++;
    }
    return (1);
}

int exit_builtins(t_command **cmd,t_gc **exec_gc, t_gc **env_gc)
{
    // int i;
    // // t_command *tmp;
    // // tmp = *cmd;
    // i = cmd_sizer(*cmd);
    // // while (tmp->cmd && tmp->cmd[i])
    // //     printf("----> %s",tmp->cmd[i++]);
    write(1, "exit\n", 5);
    if ((*cmd)->cmd && exit_parser((*cmd)->cmd[1]) == 0)
    {
        error_printer((*cmd)->cmd[1],": numeric argument required\n","exit");
        ft_gcfree(exec_gc);
        ft_gcfree(env_gc);
        exit(255);
        //return (255);
    }
    // printf("size = %d  \n", i);
    if (cmd_sizer(*cmd) > 2)
    {
        error_printer(NULL, ": too many arguments\n", "exit");
        //ft_gcfree(exec_gc);
        return (1);
    }
    //ft_gcfree(exec_gc);
    exit(EXIT_SUCCESS);
    return (0);
}
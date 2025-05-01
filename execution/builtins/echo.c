/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:14:22 by aromani           #+#    #+#             */
/*   Updated: 2025/05/01 01:09:45 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void echo_builtind(t_command *cmd)
{
    if (ft_strcmp(cmd->cmd[1] , "-n") == 0)
        ft_putstr_fd(cmd->cmd[2], 1);
    else
    {
        ft_putstr_fd(cmd->cmd[1],1);
        ft_putstr_fd("\n",1);
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:14:32 by aromani           #+#    #+#             */
/*   Updated: 2025/05/11 16:13:40 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int pwd_builtins(void)
{
    char *str;

    str = getcwd(NULL, 0);
    if (!str)
        return (perror (""), 1);
    ft_putstr(str);
    ft_putstr("\n");
    free(str);
    return (0);
}
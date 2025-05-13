/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:14:32 by aromani           #+#    #+#             */
/*   Updated: 2025/05/13 16:30:37 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int pwd_builtins(t_env **env)
{
    char *str;

    str = getcwd(NULL, 0);
    if (!str)
        str = get_env_value("PWD", *env);
    ft_putstr(str);
    ft_putstr("\n");
    free(str);
    return (0);
}
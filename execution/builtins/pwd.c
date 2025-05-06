/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:14:32 by aromani           #+#    #+#             */
/*   Updated: 2025/05/06 15:02:24 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void pwd_builtins(void)
{
    char *str;

    str = getcwd(NULL, 0);
    if (!str)
        return (perror (""));
    ft_putstr(str);
    ft_putstr("\n");
    free(str);
}
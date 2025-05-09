/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:14:27 by aromani           #+#    #+#             */
/*   Updated: 2025/04/29 16:37:05 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void exit_builtins(t_gc **gc)
{
    ft_gcfree(gc);
    write(1, "exit\n", 5);
    exit(EXIT_SUCCESS);
}
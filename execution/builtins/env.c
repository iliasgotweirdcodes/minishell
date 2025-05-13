/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:14:25 by aromani           #+#    #+#             */
/*   Updated: 2025/05/13 16:36:00 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int env_builtins(t_env **my_env)
{
     t_env *tmp;
    
    tmp = *my_env;
    while (tmp)
    {
        if (tmp->value)
        {
            ft_putstr_fd(tmp->key, 1);
            ft_putstr_fd("=", 1);
            ft_putstr_fd(tmp->value, 1);
            ft_putstr_fd("\n", 1);
        }
            //printf("%s=%s\n",tmp->key,tmp->value);
        tmp = tmp->next;
    }
    return (0);
}
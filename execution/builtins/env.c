/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:14:25 by aromani           #+#    #+#             */
/*   Updated: 2025/04/28 19:34:22 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void env_builtins(t_env **my_env, t_gc **gc)
{
    t_env *tmp;
    (void)gc;
    
    tmp = *my_env;
    while (tmp)
    {
        if (tmp->value[0] != '\0')
            printf("%s=%s\n",tmp->key,tmp->value);
        tmp = tmp->next;
    }
}
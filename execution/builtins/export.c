/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:14:30 by aromani           #+#    #+#             */
/*   Updated: 2025/05/08 17:56:52 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int export(t_env **my_env, t_command **cmd, t_gc **exec)
{
    int i;
    t_env *tmp;
    
    tmp = *my_env;
    if (!(*cmd)->cmd[1])
    {
        while (tmp)
        {
            printf("declare -x %s",tmp->key);
            if (tmp->value)
                printf("=\"%s\"\n",tmp->value);
            else
                printf("\n");
            tmp = tmp->next;
        }
        return (0);
    }
    i = add_varenv(my_env, (*cmd)->cmd[1], exec);
    if (i == 2)
        return (printf("error allocation\n"), 0);
    return (0);
}

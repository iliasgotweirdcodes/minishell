/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:14:30 by aromani           #+#    #+#             */
/*   Updated: 2025/05/13 17:39:50 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int export(t_env **my_env, t_command **cmd, t_gc **gc_env)
{
    int i;
    int j;
    t_env *tmp;
    int status;
    
    status = 0;
    tmp = *my_env;
    if (!(*cmd)->cmd[1])
    {
        while (tmp)
        {
            if (ft_strcmp(tmp->key,"_") != 0)
            {
                printf("declare -x %s",tmp->key);
                if (tmp->value)
                    printf("=\"%s\"\n",tmp->value);
                else
                    printf("\n");
            }
                tmp = tmp->next;
        }
        return (status);
    }
    j = 1;
    while ((*cmd) && (*cmd)->cmd && (*cmd)->cmd[j])
    {
        i = add_varenv(my_env, (*cmd)->cmd[j], gc_env);
        if (i == 2)
            return (printf("error allocation\n"), 1);
        if (i == -1)
            status = 1;
        j++;
    }
    return (status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:14:35 by aromani           #+#    #+#             */
/*   Updated: 2025/04/28 20:30:26 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int unset_parser(char *key)
{
    int i;
    
    i = 0;
    while (key[i])
    {
        if (!(key[i] >= 0 && key[i] <= 9) && !(key[i] >= 'a' && key[i] <= 'z') && !(key[i] >= 'A' && key[i] <= 'Z'))
            return (0);
        i++;
    }
    return (1);
}

void    unset_builtins(t_env **env, char *key)
{
    t_env *tmp;
    t_env *prev;

    if (!env || !*env || !key)
        return;
    if (unset_parser(key) == 0)
    { 
        printf("bash: unset: `%s': not a valid identifier\n", key);
        return ;
    }
    tmp = *env;
    prev = NULL;
    while (tmp != NULL)
    {
        if (ft_strcmp(tmp->key, key) == 0)
        {
            if (prev == NULL)
                *env = tmp->next;
            else
                prev->next = tmp->next;
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

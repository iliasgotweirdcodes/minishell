/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:07:36 by aromani           #+#    #+#             */
/*   Updated: 2025/05/02 02:58:23 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "../../minishell.h"
#include <string.h>

int get_eqindex(char *str, char sep)
{
    int i = 0;
    while (str[i] && str[i] != sep)
        i++;
    return i;
}

char    *ft_strdup2(const char *s, t_gc **exec)
{
    char    *new;
    size_t  len;
    size_t  i;

    if (!s)
        return (NULL);
    len = strlen(s);
    new = ft_malloc(len + 1, exec);
    if (!new)
        return NULL;
    i = 0;
    while (i < len)
    {
        new[i] = s[i];
        i++;
    }
    new[i] = '\0';
    return new;
}

char    *ft_strndup2(const char *s, size_t n, t_gc **exec)
{
    char    *new;
    size_t  i;

    if (!s)
        return (NULL);
    new = ft_malloc(n + 1, exec);
    if (!new)
        return NULL;
    i = 0;
    while (i < n && s[i])
    {
        new[i] = s[i];
        i++;
    }
    new[i] = '\0';
    return new;
}

void	env_fill(t_env **env, char **key, char **val, t_gc **exec)
{
    t_env    *new_node;
    t_env    *last;

    new_node = ft_malloc(sizeof(t_env), exec);
    if (!new_node)
    {
        write(2, "Error Allocation\n", 17);
        exit(1);
    }
    new_node->key = *key;
    new_node->value = *val;
    new_node->next = NULL;
    if (*env == NULL)
    {
        *env = new_node;
        return;
    }
    last = *env;
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
}

void get_env(char **env, t_env **my_env, t_gc **exec)
{
    size_t  i;
    size_t  eq_del;
    char *key;
    char *value;

    i = 0;
    while (env[i])
    {
        eq_del = get_eqindex(env[i], '=');
        value = ft_strdup2(env[i] + eq_del + 1, exec);
        key = ft_strndup2(env[i],eq_del, exec);
        env_fill(my_env, &key, &value, exec);
        i++;
    }

}

// void f()
// {
//     system("leaks a.out");
// }

// int main(int ac, char **av, char **env)
// {
//     atexit(f);
//     t_gc *exec = NULL;
//     t_env *my_env = NULL;
//     (void)ac;
//     (void)av;
//     //exec = malloc(sizeof(t_gc));
//     //my_env = malloc(sizeof(t_env));
//     get_env(env,&my_env,&exec);
//     //add_varenv(&my_env,"abdo=ilyas6", &exec);
//     // while(exec != NULL)
//     // {

//     //     printf("%p   \n", exec->address);
//     //     exec = exec->next;
//     // }
//     // printTheSize(&my_env, &exec);
//     // while (my_env)
//     // {
//     //     printf("%s   ||   %s\n", my_env->key, my_env->value);
//     //     my_env = my_env->next;
//     // }
//     // char **new_env = env_converter(&my_env, &exec);
//     // int i = 0;
//     // while (new_env[i] && env[i])
//     // {
//     //     if (ft_strcmp(env[i], new_env[i]) == 0)
//     //     {
//     //         printf("*************************************************************************\n");
//     //         //break ;
//     //     }
//     //     printf("%s \n", new_env[i++]);
//     // }
//     // printf("%s \n", new_env[i]);
//     ft_gcfree(&exec);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:14:17 by aromani           #+#    #+#             */
/*   Updated: 2025/04/30 18:02:30 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int get_len(char *str, char sep)
{
    int i;
    int c;

    c = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == sep)
            c++;
        i++;
    }
    return (c);
}

// char	*path_geter(char *str, char **ev)
// {
// 	int		i;
// 	size_t	j;

// 	i = 0;
// 	j = 0;
// 	while (ev[i])
// 	{
// 		while (ev[i][j] == str[j])
// 		{
// 			j++;
// 			if (ev[i][j] == str[j])
// 				j++;
// 		}
// 		if (j == ft_strlen(str))
// 			return (ev[i]);
// 		i++;
// 	}
// 	return (NULL);
// }

int cdcounter(char *path)
{
    int i;
    int c;
    int res;

    res = 0;
    i = 0;
    c = 0;
    while (path[i])
    {
        if (path[i] == '.' && path[i + 1] == '.' && path[i + 2] == '.')
            return (-1);
        if (path[i] == '.')
            c++;
        if (path[i] == '.' && path[i + 1] == '/')
            c++;
        if (c == 3)
        {
            res++;
            c = 0;
        }
        i++;
    }
    return (res);
}

// char *cdcmd_geter(char *path, char *cwd)
// {
//     int i;

//     i = 0;
//     while (path[])
// }

void go_home(t_env **s_env, t_gc **gc)
{
    char *home_path;
    char **my_env;

    my_env = env_converter(s_env, gc);
    if (!my_env)
        return ;
    home_path = path_geter("HOME", my_env);
    if(!home_path)
        return ;
    home_path = ft_strndup2(home_path + 5, ft_strlen(home_path) - 4, gc);
    if (!home_path)
        return ;
    if (chdir(home_path) == -1)
        perror("");
}

void cd_builtins(char *path, t_env **s_env, t_gc **gc)
{
    char *pwd;
    
    
    pwd = getcwd(NULL, 0);
    if (!pwd)
        return (perror(""));
    if (!path)
    {
        go_home(s_env,gc);
    }
    else if (get_len(pwd, '/') < cdcounter(path))
    {
        if (access(path, F_OK) == -1 && cdcounter(path) == -1)
            printf("minishell: cd: %s: No such file or directory", path);
        if (chdir("/") == -1)
            perror("");
    }
    else
    {
        if (access(path, F_OK) == -1)
            printf("minishell: cd: %s: No such file or directory", path);
        if (chdir(path) == -1)
            perror("");
    }
}

/// : in parent proccess : export with args && cd && exit && unset
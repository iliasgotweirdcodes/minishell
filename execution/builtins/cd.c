/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:14:17 by aromani           #+#    #+#             */
/*   Updated: 2025/05/15 20:07:13 by aromani          ###   ########.fr       */
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
    // printf("home path = %s\n",home_path);
    if (!home_path)
        return ;
    if (chdir(home_path) == -1)
        perror("");
}

// int walk_pathhandel(char *path, t_env **s_env,t_gc **gc_env)
// {
//     static int flag;

//     if (flag == 0)
//     {
//         flag++;
//         error_printer(path, ": No such file or directory\n", "cd: ");
//         return 
//     }
// }

int cd_builtins(t_command **cmd,char *path, t_env **s_env, t_gc **gc_env)
{
    char *pwd;
    //char *old = NULL;
    char *old_path = NULL;
    char *old_Pwd;
    char *new_path;
    static int flag;
    
    pwd = getcwd(NULL, 0);
    if (!pwd && path)
    {
        if (flag == 0)
        {
            flag++;
            error_printer(path, ": No such file or directory\n", "cd: ");
            //old = ft_strdup2(get_env_value("OLDPWD", *s_env), gc_env);
            return (1);
        }
        // else if (ft_strcmp(old, pwd) != 0)
        // {
        //     perror("cd: error retrieving current directory: getcwd: cannot access parent directories");
        // }
        pwd = ft_strjoinv2((*cmd)->pwd_sec, path, gc_env);
        //res = ft_strjoinv3(res ,"/..", gc_env);
        //pwd = (*cmd)->pwd_sec;
        //pwd = ft_strjoinv2((*cmd)->pwd_sec, path, gc_env);
        //pwd = ft_strjoin(pwd, path, gc_env);
        //pwd = res;
        //printf("cmd---->   %s  \n",res);
        //pwd = (*cmd)->pwd_sec;
    }
    if (!path)
    {
        go_home(s_env,gc_env);
    }
    else if (get_len(pwd, '/') < cdcounter(path))
    {
        if (access(path, F_OK) == -1 && cdcounter(path) == -1)
        {
            error_printer(NULL , ": File name too long\n", NULL);
            //printf("minishell: cd: %s: No such file or directory", path);
            return (126);
        }
        if (chdir("/") == -1)
            return (perror(""), 1);
    }
    else if (ft_strcmp(path, "-") == 0)
    {
        old_Pwd = get_env_value("OLDPWD", *s_env);
        if (!old_Pwd)
        {
            return (error_printer("OLDPWD ","not set\n","cd: "), 1);
        }
        else if (ft_strcmp(pwd, old_Pwd) != 0)
        {
            ft_putstr_fd(old_Pwd, 1);
            ft_putstr_fd("\n", 1);
            if (chdir(old_Pwd) == -1)
                return (perror("cd"), 1);
        }
        else
        {
            ft_putstr_fd(pwd, 1);
            ft_putstr_fd("\n", 1);
            if (chdir(pwd) == -1)
                return (perror("cd"), 1);
        }
    }
    else
    {
        if (chdir(path) == -1)
            return (error_printer(path, ": No such file or directory\n", "cd : "), 1);
    }
    //unset_builtins(s_env, "OLDPWD");
    old_path = ft_strjoinv3("OLDPWD=", get_env_value("PWD",*s_env), gc_env);
    if (!old_path)
        return (free(pwd), 0);
    if (is_key(s_env,old_path, gc_env) == 0)
        ft_changeval(s_env, old_path, gc_env);
    else
        add_varenv(s_env, old_path, gc_env);
    new_path = getcwd(NULL, 0);
    if (!new_path)
        new_path = pwd;
    ft_changeval(s_env, ft_strjoinv3("PWD=",new_path, gc_env), gc_env);
    //free(new_path);
    if (flag == 0)
    {
        free(pwd);
        free(new_path);
    }
    return (0);
}

// : in parent proccess : export with args && cd && exit && unset
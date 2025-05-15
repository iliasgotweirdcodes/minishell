/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:15:29 by aromani           #+#    #+#             */
/*   Updated: 2025/05/15 17:32:19 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
#include <errno.h>

int	fcheck(char *av)
{
	int	fd;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (0);
	return (close(fd), 1);
}

// char *cmd_converter(t_command **cmd_list, t_gc **gc)
// {
//     char *new_cmd;
//     int i;
//     t_command *cmd;

//     cmd = *cmd_list;
//     i = 0;
//     while (cmd)
//     {
//         if (!new_cmd)
//         {
//             new_cmd = ft_strdup2("", gc);
//             if (!new_cmd)
//                 return (NULL);
//         }
//         while (cmd->in_out[i])
//         {
//             new_cmd = ft_strjoinv3(new_cmd, cmd->in_out[i], gc);
//             if (!new_cmd)
//                 return (NULL);
//         }
//         cmd = cmd->next;
//     }
//     return (new_cmd);
// }

int keyred_counter(char **cmd)
{
    int i;
    int c;

    c = 0;
    i = 0;
    while (cmd[i])
    {
        if (ft_strcmp(cmd[i], "<") == 0 || ft_strcmp(cmd[i], ">") == 0 ||
            ft_strcmp(cmd[i], "<<") == 0 || ft_strcmp(cmd[i], ">>") == 0)
                c++;
        i++;
    }
    return (c);
}

// void error_printer(char *str)
// {
//     write(2, "minishell: ", 11);
//     perror(str);
// }


//cat << a >> a.tt << b >> b.t << c >> c.t

int redirection_handel(t_command **t_cmd)
{
    int i;
    int red_in;
    int red_out;
    t_command *tmp;

    i = 0;
    red_out = -2;
    red_in = -2;
    tmp = *t_cmd;
    while (tmp->in_out && tmp->in_out[i])
    {
        if (ft_strcmp(tmp->in_out[i], "<<") == 0)
        {
            red_in = tmp->here_docfd;
            //close(tmp->here_docfd);
            if (red_in == -100) // signal handel
                return (exit(1), 1);
            if (red_in == -1 )
                return (error_printer (tmp->in_out[i + 1], "Is a directory\n", NULL), exit(1), 1);
        }
        else if (ft_strcmp(tmp->in_out[i],"<") == 0)
        {
            if(red_in != -2)
                close(red_in);
            red_in = open(tmp->in_out[i + 1], O_RDONLY);
            if (red_in == -1)
                return (error_printer (tmp->in_out[i + 1], "Is a directory\n", NULL), exit(1), 1);
        }
        else if (ft_strcmp(tmp->in_out[i], ">>") == 0)
        {
            if (red_out != -2)
                close(red_out);
            red_out = open(tmp->in_out[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
            if (red_out == -1)
                return (error_printer (tmp->in_out[i + 1], "Is a directory\n", NULL), exit(1) ,1);
        }
        else if (ft_strcmp(tmp->in_out[i],">") == 0)
        {
            if (red_out != -2)
                close(red_out);
            red_out = open(tmp->in_out[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if (red_out == -1)
                return (error_printer (tmp->in_out[i + 1], "Is a directory\n", NULL), exit(1), 1);
        }
        i += 2;
    }
    if (red_in > 0)
    {
        // printf("red in == > %d \n", red_in);
        if (dup2(red_in, STDIN_FILENO) == -1)
            return (perror(""), exit(1), 1); 
        close(red_in);
    }
    if (red_out > 0)
    {
        if (dup2(red_out, STDOUT_FILENO) == -1)
            return (perror(""), exit(1), 1); 
        close(red_out);
    }
    return (0);
}

// char **get_valmustunseted(t_env **env, t_gc **exec)
// {
//     char **res = NULL;
//      char **m_env;
//     char *keys = NULL;
//     //t_env *tmp;
//     int i = 0;
//     m_env = env_converter(env,exec);
//     while (m_env[i])
//     {
//         printf("%s   \n", m_env[i]);
//         if (sep_exist(m_env[i],'=') != 1)
//             keys = ft_strjoinv3(ft_strjoinv3(keys, "+", exec), m_env[i], exec);
//         i++;
//     }
//     // while (tmp)
//     //     {
//     //         if (tmp->value)
//     //             printf("hello from debuger\n");
//     //         else
//     //             keys = ft_strjoinv3(ft_strjoinv3(keys, "+", exec), tmp->key, exec);
//     //         tmp = tmp->next;
//     //     }
//     // keys = ft_strdup("", exec);
//     // while (tmp)
//     // {
//     //     if (tmp->value && tmp->value[0] == '\0')
//     //         keys = ft_strjoinv3(ft_strjoinv3(keys, "+", exec), tmp->key, exec);
//     //     tmp = tmp->next;
//     // }
//        //printf("->>>>>>>>%s  \n",keys);
//     //    res = ft_split(keys, '+', exec);
//     //    if (!res)
//     //         return (NULL);
//     // while (res && res[i])
//     //     unset_builtins(env, res[i++]);
//     return (res);
// }

void chell_lvlhandel(char **cmd,t_env **env, t_gc **gc)
{
    int val = 0;
    char *new_val = NULL;
    char *key;

    if (ft_strcmp(cmd[0], "./minishell") == 0)
    {
        key = get_env_value("SHLVL",*env);
        if (key)
            val = atoi(key);
        if (val < 0)
            val = 0;
        if (val > 999)
            val = 1;
        val++;
        new_val = ft_strjoinv3("SHLVL=", ft_itoa(val, gc), gc);
        ft_changeval(env, new_val, gc);
        //get_valmustunseted(env, gc);
    }
}

int single_command(t_command **cmd, t_gc **exec_gc, t_gc **env_gc, t_env **s_env)
{
    pid_t id;
    char *path;
    int status;
    char **env;
    
    // if (!(*cmd)->cmd)
    // {
    //     status = redirection_handel(cmd);
    //     return (status);
    // }
    env = env_converter(s_env,exec_gc);
    path = last_path(env, (*cmd)->cmd, env_gc);
    status = 0;
    id = fork();
    if (id < 0)
        return (perror(""), exit(1), 1);
    if (id == 0)
    {
        
        if (!path && is_builtinns(*cmd) != 0)
        {
            if ((*cmd)->cmd != NULL)
                error_printer((*cmd)->cmd[0], ": command not found\n", NULL);
            exit(127);
            // printf("minishell: %s: command not found\n",(*cmd)->cmd[0]);
        }
        if (is_builtinns(*cmd) == 0 && is_inparent(*cmd) == 1)
        {
            redirection_handel(cmd);
            exit(builtins_execuition(cmd, s_env, exec_gc, env_gc));
        }
        else
        {
            status = redirection_handel(cmd);
        // if (!path)
        // {        
        //     error_printer((*cmd)->cmd[0], ": command not found\n", NULL);
        
        //     // printf("minishell: %s: command not found\n",(*cmd)->cmd[0]);
        //     exit(127);
        // }
        if (opendir(path) != NULL)
            return (error_printer((*cmd)->cmd[0], ": is a directory\n", NULL), exit(126), 1);
        if (execve(path, (*cmd)->cmd, env) == -1)
        {
            perror("execve");
            exit(126);
        }
        }
    }
    else
    {
        wait(&status); 
        return  WEXITSTATUS(status);
    }
    // while (wait(0) != -1)
    //     ;
    return WEXITSTATUS(status);
}

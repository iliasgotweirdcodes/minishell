/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:32:17 by aromani           #+#    #+#             */
/*   Updated: 2025/05/09 18:29:54 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int singel_pipe(t_command **cmd, char *path, t_gc **exec, t_env **s_env)
{
    int id;
    int fd[2];
    char **env;

    env = env_converter(s_env, exec);
    if (pipe(fd) == -1)
        perror("");
    id = fork();
    if (id == -1)
        perror("");
    if (id == 0)
    {

        close(fd[0]);
        dup2(fd[1],1);
        close(fd[1]);
        redirection_handel(cmd);
        if (is_builtinns(*cmd) == 0)
        {
            builtins_execuition(cmd, s_env, exec);
            exit(0);
        }
        else
        {
            if (path)
            {
                if (opendir(path) != NULL)
                    return (error_printer(path), exit(126),1);
                if (execve(path,(*cmd)->cmd,env) < 0)
                    perror("");
            }
            close(fd[0]);
            close(fd[1]);
            exit(1);
        }
    }
    else
    {
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
    }
    return (0);
}



int last_command(t_command **cmd, char **env, t_gc **exec, t_env **struct_env)
{
    pid_t id;
    char *path;

    path = last_path(env, (*cmd)->cmd, exec);
    if (!path && is_builtinns(*cmd) != 0)
    {
        printf("minishell: %s: command not found\n",(*cmd)->cmd[0]);
        return (1);
    }
    if (is_builtinns(*cmd) == 0)
    {
        redirection_handel(cmd);
        builtins_execuition(cmd, struct_env, exec);
    }
    id = fork();
    if (id < 0)
        return (perror(""), exit(1), 1);
    if (id == 0)
    {
        if(is_builtinns(*cmd) != 0)
        {
            redirection_handel(cmd);
            if (opendir(path) != NULL)
                return (error_printer(path), exit(126),1);
            if (execve(path, (*cmd)->cmd, env) == -1)
            {
                perror("execve :");
                exit(1);
            }
        }
    }
    return (0);
}

int multi_cmd(char **env, t_command **cmd,t_gc **exec, t_env **s_env)
{
    t_command *tmp;
    char *path;

    tmp = *cmd;
    while (tmp && tmp->next)
    {
        //printf("<<<<<<<<<hi from multi>>>>>>>>> cmd  =  %s \n",tmp->cmd[0]);

        path = last_path(env, tmp->cmd, exec);
        if (!path && is_builtinns(tmp) != 0)
        {
            if (tmp->cmd != NULL)
                printf("minishell: %s: command not found\n",(*cmd)->cmd[0]);
        }
        singel_pipe(&tmp, path, exec, s_env);
        tmp = tmp->next;
    }
    if (tmp)
        last_command(&tmp,env,exec,s_env);
    return (0);
}

// //sigpipe
// while true; do
// leaks minishell
// sleep 10
// done
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:32:17 by aromani           #+#    #+#             */
/*   Updated: 2025/05/13 16:23:08 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int singel_pipe(t_command **cmd, char *path, t_gc **exec, t_env **s_env)
{
    int id;
    int fd[2];
    char **env;
    int status;
    t_command *tmp;

    status = 0;
    tmp = *cmd;
    env = env_converter(s_env, exec);
    if (pipe(fd) == -1)
        return (perror(""), exit(1), 1);
    id = fork();
    if (id == -1)
        return (perror(""), exit(1), 1);
    if (id == 0)
    {
        
        close(fd[0]);
        dup2(fd[1],1);
        close(fd[1]);
        redirection_handel(cmd);
        if (!path && is_builtinns(tmp) != 0)
        {
            if (tmp->cmd != NULL)
                error_printer((*cmd)->cmd[0], ": command not found\n", NULL);
            exit(127);
            // printf("minishell: %s: command not found\n",(*cmd)->cmd[0]);
        }
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
                    return (error_printer(path, "is a directory\n", NULL), exit(126),1);
                if (execve(path,(*cmd)->cmd,env) < 0)
                    return (perror(""), exit(127), 1);
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
        //waitpid(id,&status, 0); 
    }
    
    return WEXITSTATUS(status);
}



int last_command(t_command **cmd, char **env, t_gc **exec, t_env **struct_env)
{
    pid_t id;
    char *path;
    int status;

    status = 0;
    path = last_path(env, (*cmd)->cmd, exec);
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
            if (!path && is_builtinns(*cmd) != 0)
            {
                if ((*cmd)->cmd)
                    error_printer((*cmd)->cmd[0], ": command not found\n", NULL);
                //printf("minishell: %s: command not found\n",(*cmd)->cmd[0]);
                exit(127);
            }
            if (opendir(path) != NULL)
                return (error_printer(path, "is a directory\n", NULL), exit(126),1);
            if (execve(path, (*cmd)->cmd, env) == -1)
            {
                perror("execve :");
                exit(126);
            }
        }
    }
    else
    {
        waitpid(id,&status, 0); 
    }

    return WEXITSTATUS(status);
    // status = WEXITSTATUS(id);
}

int multi_cmd(char **env, t_command **cmd,t_gc **exec, t_env **s_env)
{
    t_command *tmp;
    char *path;
    int status;

    status = 0;
    tmp = *cmd;
    while (tmp && tmp->next)
    {
        //printf("<<<<<<<<<hi from multi>>>>>>>>> cmd  =  %s \n",tmp->cmd[0]);

        path = last_path(env, tmp->cmd, exec);
        // if (!path && is_builtinns(tmp) != 0)
        // {
        //     if (tmp->cmd != NULL)
        //         error_printer((*cmd)->cmd[0], ": command not found\n", NULL);
                
        //     // printf("minishell: %s: command not found\n",(*cmd)->cmd[0]);
        // }
        singel_pipe(&tmp, path, exec, s_env);
        tmp = tmp->next;
    }
    if (tmp)
        status = last_command(&tmp,env,exec,s_env);
  
    return (status);
}

// //sigpipe
// while true; do
// lsof -c minishell
// sleep 10
// done
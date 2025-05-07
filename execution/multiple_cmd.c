/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:32:17 by aromani           #+#    #+#             */
/*   Updated: 2025/05/07 19:57:56 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void singel_pipe(char **env, t_command **cmd, char *path, t_gc **exec)
{
    int id;
    int fd[2];

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
            builtins_execuition(cmd, (*cmd)->env_ptr, exec);
            exit(0);
        }
        else
        {
            if (path)
            {
                // close(fd[0]);
                // dup2(fd[1],1);
                // close(fd[1]);
                printf("hi from execve runner\n");
                if (execve(path,(*cmd)->cmd,env) < 0)
                    perror("");
            }
            exit(1);
        }
    }
    else
    {
        printf("hi from else pipe \n");
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
    }

}



int last_command(t_command **cmd, char **env, t_gc **exec)
{
    pid_t id;
    char *str;

    str = last_path(env, (*cmd)->cmd, exec);
    if (!str)
    {
        printf("minishell: %s: command not found\n",(*cmd)->cmd[0]);
        return (1);
    }
    id = fork();
    if (id < 0)
        return (perror(""), exit(1), 1);
    if (id == 0)
    {
        redirection_handel(cmd);
        if (is_builtinns(*cmd) == 0)
            builtins_execuition(cmd, (*cmd)->env_ptr, exec);
        else
        {
            if (execve(str, (*cmd)->cmd, env) == -1)
            {
                perror("execve :");
                exit(1);
            }
        }
    }
    return (0);
}

int multi_cmd(char **env, t_command **cmd,t_gc **exec)
{
    t_command *tmp;
    char *path;

    tmp = *cmd;
    while (tmp && tmp->next)
    {
        printf("<<<<<<<<<hi from multi>>>>>>>>> cmd  =  %s \n",tmp->cmd[0]);

        path = last_path(env, tmp->cmd, exec);
        if (!path)
        {
            printf("minishell: %s: command not found\n",(*cmd)->cmd[0]);
        }
        singel_pipe(env, &tmp, path, exec);
        tmp = tmp->next;
    }
    if (tmp)
        last_command(&tmp,env,exec);
    return (0);
}

//sigpipe

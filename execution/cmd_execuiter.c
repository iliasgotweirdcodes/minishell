/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execuiter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:57:50 by aromani           #+#    #+#             */
/*   Updated: 2025/05/07 20:54:01 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_cmdsize(t_command **cmd)
{
    int i;
    t_command *tmp;

    tmp = *cmd;
    i = 0;
    while (tmp)
    {
        tmp=tmp->next;
        i++;
    }
    return (i);
}

int is_builtinns(t_command *cmd)
{
    if (!cmd->cmd)
        return (1);
    if ((ft_strcmp(cmd->cmd[0], "cd") == 0 || ft_strcmp(cmd->cmd[0], "echo") == 0 
        || ft_strcmp(cmd->cmd[0], "pwd") == 0 || ft_strcmp(cmd->cmd[0], "export") == 0
        || ft_strcmp(cmd->cmd[0], "unset") == 0 || ft_strcmp(cmd->cmd[0], "env") == 0
        || ft_strcmp(cmd->cmd[0], "exit") == 0))
            return (0);
    return (1);
}

int builtins_execuition(t_command **cmd, t_env **env, t_gc **exec)
{
    if (ft_strcmp((*cmd)->cmd[0], "cd") == 0 )
        return (cd_builtins((*cmd)->cmd[1], env, exec), 0);
    else if(ft_strcmp((*cmd)->cmd[0], "echo") == 0)
        return (echo_builtind(*cmd), 0);
    else if(ft_strcmp((*cmd)->cmd[0], "pwd") == 0)
        return (pwd_builtins(), 0);
    else if(ft_strcmp((*cmd)->cmd[0], "export") == 0)
        return (export(env, cmd, exec), 0);
    else if(ft_strcmp((*cmd)->cmd[0], "unset") == 0)
        return (unset_builtins(env,(*cmd)->cmd[1]), 0);
    else if(ft_strcmp((*cmd)->cmd[0], "env") == 0)
        return (env_builtins(env,exec), 0);
    else if(ft_strcmp((*cmd)->cmd[0], "exit") == 0)
        return (exit_builtins(exec), 0);
    return (1);
}

int cmd_execuiter(t_command **cmd_list, t_env **s_env, t_gc **exec)
{
    t_command *cmd;
    char **my_env;
    int fd[2];
    static int flag;
    //struct termios old_stdin;

    fd[0] = dup(0);
    fd[1] = dup(1);
    //tcgetattr(1,&old_stdin);
    if (flag == 0)
    {
        unset_builtins(s_env,"OLDPWD");
        flag = 1;
    }
    my_env = env_converter(s_env, exec);
    if (!my_env)
        return (1);
    cmd = *cmd_list;
    cmd->env_ptr = s_env;
    if (ft_cmdsize(cmd_list) == 1)
    {
        if (is_builtinns(cmd) == 0)
        {
            printf("hello from builtins \n");
            redirection_handel(cmd_list);
            builtins_execuition(cmd_list, s_env, exec);
        }
        else
            single_command(cmd_list, my_env, exec, s_env);
    }else
        multi_cmd(my_env, cmd_list, exec);
    //tcsetattr(1,0,&old_stdin);
    dup2(fd[0], 0);
    dup2(fd[1], 1);
    close(fd[0]);
    close(fd[1]);
    while (wait(0) != -1)
        ;
    // printf("hunged place\n");
    // if ()
    return (0);
}

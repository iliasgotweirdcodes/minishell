/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execuiter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:57:50 by aromani           #+#    #+#             */
/*   Updated: 2025/05/02 02:53:26 by aromani          ###   ########.fr       */
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
    if (ft_strcmp(cmd->cmd[0], "cd") == 0 || ft_strcmp(cmd->cmd[0], "echo") == 0 
        || ft_strcmp(cmd->cmd[0], "pwd") == 0 || ft_strcmp(cmd->cmd[0], "export") == 0
        || ft_strcmp(cmd->cmd[0], "unset") == 0 || ft_strcmp(cmd->cmd[0], "env") == 0
        || ft_strcmp(cmd->cmd[0], "exit") == 0)
            return (0);
    return (1);
}

void builtins_execuition(t_command **cmd, t_env **env, t_gc **exec)
{
    if (ft_strcmp((*cmd)->cmd[0], "cd") == 0 )
        cd_builtins((*cmd)->cmd[1], env, exec);
    else if(ft_strcmp((*cmd)->cmd[0], "echo") == 0)
        echo_builtind(*cmd);
    else if(ft_strcmp((*cmd)->cmd[0], "pwd") == 0)
        pwd_builtins();
    else if(ft_strcmp((*cmd)->cmd[0], "export") == 0)
        export(env, cmd, exec);
    else if(ft_strcmp((*cmd)->cmd[0], "unset") == 0)
        unset_builtins(env,(*cmd)->cmd[1]);
    else if(ft_strcmp((*cmd)->cmd[0], "env") == 0)
        env_builtins(env,exec);
    else if(ft_strcmp((*cmd)->cmd[0], "exit") == 0)
        exit_builtins(exec);
}

void cmd_execuiter(t_command **cmd_list, t_env **env, t_gc **exec)
{
    t_command *cmd;
    char **my_env;
    int fd[2];
    struct termios old_stdin;

    fd[0] = dup(0);
    fd[1] = dup(1);
    tcgetattr(1,&old_stdin);
    my_env = env_converter(env, exec);
    if (!my_env)
        return ;
    cmd = *cmd_list;
    cmd->env_ptr = env;
    if (ft_cmdsize(cmd_list) == 1)
    {
        if (is_builtinns(cmd) == 0)
        {
            printf("hello from builtins \n");
            redirection_handel(cmd_list);
            builtins_execuition(cmd_list, env, exec);
        }
        else
            single_command(cmd_list, my_env, exec);
    }else
        multi_cmd(my_env, cmd_list, exec);
    tcsetattr(1,0,&old_stdin);
    dup2(fd[0], 0);
    dup2(fd[1], 1);
    while (wait(0) != -1)
        ;
}

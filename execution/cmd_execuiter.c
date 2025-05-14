/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execuiter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:57:50 by aromani           #+#    #+#             */
/*   Updated: 2025/05/14 17:08:46 by aromani          ###   ########.fr       */
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

int builtins_execuition(t_command **cmd, t_env **env, t_gc **exec, t_gc **env_gc)
{
    int status;

    status = 0;
    if (ft_strcmp((*cmd)->cmd[0], "cd") == 0 )
        status = cd_builtins(cmd ,(*cmd)->cmd[1], env, env_gc);
    else if(ft_strcmp((*cmd)->cmd[0], "echo") == 0)
        status = echo_builtind(cmd);
    else if(ft_strcmp((*cmd)->cmd[0], "pwd") == 0)
        status = pwd_builtins(env);
    else if(ft_strcmp((*cmd)->cmd[0], "export") == 0)
        status = export(env, cmd, env_gc);
    else if(ft_strcmp((*cmd)->cmd[0], "unset") == 0)
        status = unset_builtins(env, cmd, exec);
    else if(ft_strcmp((*cmd)->cmd[0], "env") == 0)
        status = env_builtins(env);
    else if(ft_strcmp((*cmd)->cmd[0], "exit") == 0)
        status = exit_builtins(cmd,exec, env_gc);
    else
        return (-1);
    //g_exit_status = status;
    return (status);
}

void pwd_set(t_command **cmd, t_env **env, t_gc **gc_exec)
{
	t_command *tmp;
	static char *old_pwd;
	char *pwd;

	pwd = ft_strdup2(get_env_value("PWD", *env), gc_exec);
    old_pwd = ft_strdup2(get_env_value("OLPWD", *env), gc_exec);
	tmp = *cmd;
	while (tmp)
	{
		if (pwd)
			tmp->pwd_sec = pwd;
        if (old_pwd && old_pwd[0] == '\0')
            tmp->oldpwd_set = NULL;
        else
            tmp->oldpwd_set = old_pwd;
		tmp = tmp->next;
	}
	old_pwd = pwd;
}

void param_adds(t_env **s_env, t_gc **env_gc)
{
    char *pwd;
    char *pwd_path;
    
    pwd = getcwd(NULL, 0);
    if (!pwd)
        perror("") ;
    pwd_path = ft_strjoinv3("PWD=", pwd, env_gc);
    add_varenv(s_env,pwd_path, env_gc);
    unset_management(s_env,"OLDPWD",env_gc);
    add_varenv(s_env, "OLDPWD", env_gc);
    ft_changeval(s_env,"_=/usr/bin/env", env_gc);
    free(pwd);
}

int cmd_execuiter(t_command **cmd_list, t_env **s_env, t_gc **exec, t_gc **env_gc)
{
    t_command *cmd;
    char **my_env;
    int fd[2];
    int status;

    status = 0;
    fd[0] = dup(0);
    fd[1] = dup(1);
    my_env = env_converter(s_env, exec);
    if (!my_env)
        return (1);
    cmd = *cmd_list;
    if (ft_cmdsize(cmd_list) == 1)
    {
        if (is_builtinns(cmd) == 0)
        {
            redirection_handel(cmd_list);
            status = builtins_execuition(cmd_list, s_env, exec, env_gc);
        }
        else
            status = single_command(cmd_list, my_env, exec);
    }else
        status = multi_cmd(cmd_list, exec,s_env, env_gc);
    dup2(fd[0], 0);
    dup2(fd[1], 1);
    close(fd[0]);
    close(fd[1]);
    while (wait(0) != -1)
        ;
    return (status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singlecmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:15:29 by aromani           #+#    #+#             */
/*   Updated: 2025/04/22 16:05:32 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fcheck(char *av)
{
	int	fd;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (0);
	return (close(fd), 1);
}

void redirection_handel(int heredoc_fd,t_command *t_cmd)
{
    int i;
    int fd;

    i = 0;
    while (t_cmd->in_out[i])
    {
        if (t_cmd->in_out[i] == '<' || t_cmd->in_out[i] == '>')
        {
            if (fcheck(t_cmd->in_out[i+1]) == 1)
            {
                fd = open(av,O_RDONLY);
                if (t_cmd->in_out[i] == '<')
                    dup2(fd, 0);
                else if (t_cmd->in_out[i] == '>')
                    dup2(fd, 1);
            }
        }
        else if ( ft_strcmp(t_cmd->in_out[i], "<<") == 0)
            dup2(heredoc_fd, 0);
        i++;
    }   
}

void single_command(char **cmd, char **env, t_command *t_cmd)
{
    pid_t id;
    char *str;

    str = last_path(env, cmd);
    if (!str)
        return ;
    id = fork();
    if (id < 0)
        return (perror("error \n"), exit(1));
    if (id == 0)
    {
        redirection_handel(t_cmd->here_docfd,t_cmd);
        if (execve(str, cmd, env) == -1)
            perror("execve :");
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:28:34 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/05/17 16:40:27 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void siginthandle(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		exit(1);
	}
}

int	hanlde_here_doc(char *delimiter)
{
	char	*line;
	int		fd[2];
	int id;
	int status;

	status = 0;

	unlink("here_doc");
	fd[0] = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	fd[1] = open("here_doc", O_RDONLY, 0777);
	unlink("here_doc");
	id = fork();
	if (id == 0)
	{
		signal(SIGINT, siginthandle);
		while (1)
		{
			line = readline("> ");
			if (!line)
			{
				close(fd[0]);
				exit(0);
				//break ;
			}
			if (ft_strcmp(line, delimiter) == 0)
			{
				free(line);
				close(fd[0]);
				exit(0);
				//break;
			}
			write(fd[0], line, ft_strlen(line));
			write(fd[0], "\n", 1);
			free(line);
		}
}
	// wait(&status);
	else
		waitpid(id,&status, 0);
	status = WEXITSTATUS(status);
	if (status == 1)
	{
		close(fd[0]);
		close(fd[1]);
		return(-100); // in case of ctr + c signal
	}
	return (close(fd[0]),fd[1]);
	// return (fd[1]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:28:34 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/05/14 23:21:45 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	hanlde_here_doc(char *delimiter)
{
	char	*line;
	int		fd[2];

	unlink("here_doc");
	fd[0] = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	fd[1] = open("here_doc", O_RDONLY, 0777);
	unlink("here_doc");
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(fd[0]);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			close(fd[0]);
			break ;
		}
		write(fd[0], line, ft_strlen(line));
		write(fd[0], "\n", 1);
		free(line);
	}
	return (fd[1]);
}

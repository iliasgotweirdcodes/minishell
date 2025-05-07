/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:28:34 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/05/07 22:59:58 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int	ft_here_doc(char *delimiter)
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

void	ft_handle_err_here_doc(t_token *tokens)
{
	t_token	*current;
	int		fd;

	fd = 0;
	current = tokens;
	while (current)
	{
		if (current->type == HEREDOC)
		{
			fd = ft_here_doc(current->next->value);
			current->here_docfd = fd;
			break ;
		}
		current = current->next;
	}
	close(fd);
}

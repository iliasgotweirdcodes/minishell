/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:28:34 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/04/23 19:04:23 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*st1;
	unsigned char	*st2;

	i = 0;
	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	while (st1[i] || st2[i])
	{
		if (st1[i] != st2[i])
			return (st1[i] - st2[i]);
		i++;
	}
	return (0);
}
int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	hanlde_here_doc(char *delimiter)
{
	char *line;
	int fd[2];

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
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

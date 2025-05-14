/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:54:52 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/05/14 23:14:22 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	count_cmd(t_token *tokens)
{
	t_token	*current;
	size_t	cmd_count;

	cmd_count = 0;
	current = tokens;
	while (current)
	{
		if (current->type == WORD && current->value)
		{
			if (!current->prev || !is_redirection(current->prev->type))
				cmd_count++;
		}
		current = current->next;
	}
	return (cmd_count);
}

char	*get_cmd(t_token *tokens, t_gc **gc)
{
	char	*cmd_line;
	char	*temp;
	t_token	*current;

	cmd_line = NULL;
	current = tokens;
	while (current)
	{
		if (current->type == WORD)
		{
				temp = ft_strjoin(cmd_line, " ", gc);
				cmd_line = ft_strjoin(temp, current->value, gc);
				if (!cmd_line)
					return (NULL);
			current = current->next;
		}
		if (current && is_redirection(current->type))
		{
			current = current->next;
			current = current->next;
		}
	}
	return (cmd_line);
}

char	**prepare_cmd(t_token *tokens, t_gc **gc)
{
	char	**str_cmd;
	char	*cmd_line;

	cmd_line = get_cmd(tokens, gc);
	if (!cmd_line)
		return (NULL);
	printf("cmd_line = %s\n", cmd_line);
	str_cmd = ft_split_vtab(cmd_line, gc);
	int i = 0;
	while (str_cmd[i])
	{
		printf("str_cmd[%d]: %s\n", i, str_cmd[i]);
		i++;
	}
	if (!str_cmd)
		return (NULL);
	return (str_cmd);
}


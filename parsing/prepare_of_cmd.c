/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_of_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:22:35 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/04/24 21:16:08 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_pipe(t_token *tokens)
{
	if (tokens->type == PIPE)
		return (1);
	return (0);
}

size_t	count_cmd(t_token **tokens)
{
	t_token	*current;
	size_t		cmd_count;

	cmd_count = 0;
	current = *tokens;
	while (current)
	{
		if (current->type == WORD)
		{
			if (!current->prev || !is_redirection(current->prev->type))
				cmd_count++;
		}
		current = current->next;
	}
	return (cmd_count);
}

char *get_cmdline(t_token **tokens)
{
	char	*cmd_line;
	char	*temp;
	t_token	*current;

	cmd_line = NULL;
	current = *tokens;
	while (current)
	{
		if (current->type == WORD && (!current->prev || !is_redirection(current->prev->type)))
		{
			temp = ft_strjoin(cmd_line, " ");
			free(cmd_line);
			cmd_line = ft_strjoin(temp, current->value);
			free(temp);
			if (!cmd_line)
				return (NULL);
		}
		current = current->next;
	}
	return (cmd_line);
}

void prepare_cmd(t_command **cmd, t_token *tokens)
{
	char	**tmp;
	char	*cmd_line;

	cmd_line = get_cmdline(&tokens);
	if (!cmd_line || !*cmd_line)
	{
		free(cmd_line);
		return ;
	}
	tmp = ft_split(cmd_line, ' ');
	if (!tmp)
	{
		free(cmd_line);
		return ;
	}
	*cmd = ft_lstnew(tmp);
	printf("cmd_line = %s\n", cmd_line);
	free(cmd_line);
}

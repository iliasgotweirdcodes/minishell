/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_in_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 19:23:19 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/05/05 20:22:28 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_redir(t_token_type type)
{
	if (type == REDIR_IN)
		return ("<");
	else if (type == REDIR_OUT)
		return (">");
	else if (type == HEREDOC)
		return ("<<");
	else if (type == APPEND)
		return (">>");
	return (NULL);
}

size_t count_in_out(t_token *tokens)
{
	t_token	*current;
	size_t	count;

	count = 0;
	current = tokens;
	while (current)
	{
		if (is_redirection(current->type))
			count++;
		current = current->next;
	}
	return (count);
}

char *get_in_out(t_token *tokens, t_gc **gc)
{
	char	*in_out;
	char	*temp;
	t_token	*current;

	in_out = NULL;
	current = tokens;
	while (current)
	{
		if (is_redirection(current->type))
		{
			if (!in_out)
				in_out = ft_strdup(current->value, gc);
			else
			{
				temp = ft_strjoin(in_out, " ", gc);
				in_out = ft_strjoin(temp, current->value, gc);
			}
			if (!in_out)
				return (NULL);
		}
		current = current->next;
	}
	return (in_out);
}


char	**prepare_in_out(t_token *tokens, t_gc **gc)
{
	t_token	*current;
	char	**in_out;
	int		count;
	int		i;

	count = count_in_out(tokens) * 2;
	if (count == 0)
		return (NULL);
	in_out = ft_malloc(sizeof(char *) * (count + 1), gc);
	if (!in_out)
		return (NULL);
	current = tokens;
	i = 0;
	while (current)
	{
		if (is_redirection(current->type))
		{
			in_out[i++] = get_redir(current->type);
			if (current->next && current->next->type == WORD)
				in_out[i++] = ft_strdup(current->next->value, gc);
			else
				in_out[i++] = ft_strdup("MISSING_FILE", gc);
			current = current->next;
		}
		current = current->next;
	}
	in_out[i] = NULL;
	return (in_out);
}

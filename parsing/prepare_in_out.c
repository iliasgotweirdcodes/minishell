/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_in_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 19:23:19 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/05/17 18:15:22 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_redirection(t_token_type type)
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

// char *get_in_out(t_token *tokens, t_gc **gc)
// {
// 	char	*in_out = NULL;
// 	char	*temp;
// 	t_token	*current = tokens;

// 	while (current)
// 	{
// 		if (is_redirection(current->type))
// 		{
// 			if (!in_out)
// 				in_out = ft_strdup(current->value, gc);
// 			else
// 			{
// 				temp = ft_strjoin(in_out, " ", gc);
// 				in_out = ft_strjoin(temp, current->value, gc);
// 			}
// 			if (current->next && current->next->type == WORD)
// 			{
// 				temp = ft_strjoin(in_out, " ", gc);
// 				in_out = ft_strjoin(temp, current->next->value, gc);
// 			}
// 			if (!in_out)
// 				return (NULL);
// 		}
// 		current = current->next;
// 	}
// 	printf("in_out str >> %s\n", in_out);
// 	return (in_out);
// }

char	*get_in_out(t_token *tokens, t_gc **gc)
{
	t_token	*current;
	char	*in_out = NULL;
	char	*temp;

	current = tokens;
	while (current)
	{
		if (is_redirection(current->type))
		{
			if (!in_out)
				in_out = ft_strdup(get_redirection(current->type), gc);
			else
			{
				temp = ft_strjoin(in_out, " ", gc);
				in_out = ft_strjoin(temp, get_redirection(current->type), gc);
			}
			if (current->next && current->next->type == WORD)
			{
				temp = ft_strjoin(in_out, " ", gc);
				in_out = ft_strjoin(temp, current->next->value, gc);
			}
			current = current->next;
		}
		current = current->next;
	}
	return (in_out);
}

char	**prepare_in_out(t_token *tokens, t_gc **gc)
{
	char	**in_out;
	char	*str_in_out;

	str_in_out = get_in_out(tokens, gc);
	if (!str_in_out)
		return (NULL);
	in_out = ft_split_quotes(str_in_out, gc);
	if (!in_out)
		return (NULL);
	remove_quotes(in_out, gc);
	return (in_out);
}

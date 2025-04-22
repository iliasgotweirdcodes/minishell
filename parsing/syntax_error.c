/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:58:22 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/04/22 02:16:24 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	is_redirection(t_token_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == APPEND || type == HEREDOC);
}

int	check_redirection(t_token *token)
{
	if (!token->next || token->next->type != WORD)
	{
		if (token->next)
			print_syntax_error(token->next->value);
		else
			print_syntax_error("newline");
		return (1);
	}
	return (0);
}

int	check_consecutive_ops(t_token *prev, t_token *current)
{
	if (is_operator(prev->type) && is_operator(current->type))
	{
		print_syntax_error(current->value);
		return (1);
	}
	return (0);
}

int	validate_syntax(t_token *tokens)
{
	t_token	*current;
	t_token	*prev;

	current = tokens;
	prev = NULL;
	if (!tokens)
		return (0);
	if (current->type == PIPE)
		return (print_syntax_error("|"), 1);
	while (current)
	{
		// Check redirections have valid targets
		if (is_redirection(current->type) && check_redirection(current))
			return (1);
		// Check for invalid consecutive operators
		if (prev && check_consecutive_ops(prev, current))
			return (1);
		prev = current;
		current = current->next;
	}
	// Check dangling operator at end
	if (prev && is_operator(prev->type))
		return (print_syntax_error("newline"), 1);
	return (0);
}

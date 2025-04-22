/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:58:22 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/04/22 21:13:30 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Check if a character is an operator
int	is_redirection(t_token_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == APPEND || type == HEREDOC);
}
// Check if a TOKEN TYPE is an operator (used during syntax validation)
int	is_operator(t_token_type type)
{
	return (type == PIPE || type == REDIR_IN ||
			type == REDIR_OUT || type == APPEND || type == HEREDOC);
}

// Check if a character is a quote
// int	check_redirection(t_token *token)
// {
// 	if (!token->next || token->next->type != WORD)
// 	{
// 		if (token->next)
// 			print_syntax_error(token->next);
// 		else
// 			print_syntax_error(NULL);
// 		return (1);
// 	}

// 	return (0);
// }

// Check if two consecutive tokens are operators
// int	check_consecutive_ops(t_token *prev, t_token *current)
// {
// 	if (is_operator(prev->type) && is_operator(current->type))
// 	{
// 		print_syntax_error(current);
// 		return (1);
// 	}
// 	return (0);
// }

int validate_syntax(t_token *tokens)
{
    t_token *current = tokens;
    t_token *prev = NULL;

    if (!tokens)
        return (0);
    // Check for leading pipe
    if (current->type == PIPE)
        return (print_syntax_error(current), 1);
    while (current)
    {
        // Check consecutive operators (e.g., ">> |" or "> >")
        if (prev && is_operator(prev->type) && is_operator(current->type))
            return (print_syntax_error(current), 1);
        // Check redirection followed by pipe (e.g., "> |")
        if (prev && is_redirection(prev->type) && current->type == PIPE)
            return (print_syntax_error(current), 1);
        // Check invalid redirection target
        if (is_redirection(current->type) && (!current->next || current->next->type != WORD))
            return (print_syntax_error(current->next), 1);
        prev = current;
        current = current->next;
    }
    // Check dangling operator at end (e.g., "ls |")
    if (prev && is_operator(prev->type))
        return (print_syntax_error(NULL), 1);
    return (0);
}

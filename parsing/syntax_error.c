/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:58:22 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/04/22 23:44:40 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redirection(t_token_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == APPEND || type == HEREDOC);
}

int	is_operator(t_token_type type)
{
	return (type == PIPE || type == REDIR_IN ||
			type == REDIR_OUT || type == APPEND || type == HEREDOC);
}

int	validate_syntax(t_token *tokens)
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

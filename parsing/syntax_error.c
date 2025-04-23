/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:58:22 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/04/23 20:42:15 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redirection(t_token_type type)
{
    if (type == REDIR_IN || type == REDIR_OUT
        || type == APPEND || type == HEREDOC)
        return (1);
    return (0);
}

int	is_operator(t_token_type type)
{
    if (type == PIPE || is_redirection(type))
        return (1);
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
        return (print_syntax_error(current), 1);
    while (current)
    {
         if (current->type == HEREDOC)
        {
           printf("HEREDOC HEREEEEEE FIRST\n");
            if (current->next && current->next->type == WORD)
            {
                prev = current->next;
                current = current->next->next;
                continue;
            }
            else
            {
                print_syntax_error(current->next ? current->next : current);
                return (1);
            }
        }
        if (prev && is_operator(prev->type) && is_operator(current->type))
            return (print_syntax_error(current), 1);
        if (prev && is_redirection(prev->type) && current->type == PIPE)
            return (print_syntax_error(current), 1);
        if (is_redirection(current->type))
        {
            if (!current->next || current->next->type != WORD)
                return (print_syntax_error(current->next), 1);
        }
        prev = current;
        current = current->next;
    }
    if (prev && is_operator(prev->type))
        return (print_syntax_error(NULL), 1);
    return (0);
}

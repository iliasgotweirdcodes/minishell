/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 00:17:02 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/05/15 19:27:03 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char	*get_operator_symbol(t_token_type type)
{
	if (type == PIPE)
		return ("|");
	if (type == REDIR_IN)
		return ("<");
	if (type == REDIR_OUT)
		return (">");
	if (type == APPEND)
		return (">>");
	if (type == HEREDOC)
		return ("<<");
	return ("");
}

void	print_syntax_error(t_token *token)
{
	char	*value;

	value = "newline";
	if (token)
	{
		if (token->type == WORD)
			value = token->value;
		else
			value = get_operator_symbol(token->type);
	}
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(value, 2);
	ft_putstr_fd("'\n", 2);
}

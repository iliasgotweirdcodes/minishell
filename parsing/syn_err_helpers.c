/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn_err_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 01:24:43 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/04/22 02:10:36 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '(' || c == ')');
}

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}
int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

void	print_syntax_error(char *token)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	if (token)
		write(2, token, ft_strlen(token));
	else
		write(2, "newline", 7);
	write(2, "'\n", 2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:01:13 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/04/22 01:36:47 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_shell_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

static void	handle_escape(char *input, int *i)
{
	(*i)++;
	if (input[*i])
		(*i)++;
}

static void	handle_operator(char *input, int *i, t_token **token_list)
{
	if (input[*i] == '|')
	{
		ft_add_token(token_list, ft_create_token(PIPE, NULL));
		(*i)++;
	}
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		ft_add_token(token_list, ft_create_token(HEREDOC, NULL));
		*i += 2;
	}
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		ft_add_token(token_list, ft_create_token(APPEND, NULL));
		*i += 2;
	}
	else if (input[*i] == '<')
	{
		ft_add_token(token_list, ft_create_token(REDIR_IN, NULL));
		(*i)++;
	}
	else if (input[*i] == '>')
	{
		ft_add_token(token_list, ft_create_token(REDIR_OUT, NULL));
		(*i)++;
	}
}

static void	handle_word(char *input, int *i, t_token **token_list)
{
	int		start;
	char	quote;
	char	*value;

	start = *i;
	quote = 0;
	while (input[*i] && (quote || (!isspace(input[*i])
		&& !is_shell_operator(input[*i]))))
	{
		if (input[*i] == '\\' && !quote)
			handle_escape(input, i);
		else if ((input[*i] == '\'' || input[*i] == '"') && !quote)
			quote = input[(*i)++];
		else if (input[*i] == quote && quote)
			quote = 0 * (*i)++;
		else
			(*i)++;
	}
	if (quote)
		return (print_syntax_error("minishell: unclosed quote"), (void)0);
	value = ft_strndup(input + start, *i - start);
	if (!value)
		return (ft_clear_tokens(token_list), (void)0);
	ft_add_token(token_list, ft_create_token(WORD, value));
}

t_token	*ft_tokenization(char *input)
{
	t_token	*token_list;
	int		i;

	token_list = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			handle_operator(input, &i, &token_list);
		else
			handle_word(input, &i, &token_list);
	}
	return (token_list);
}

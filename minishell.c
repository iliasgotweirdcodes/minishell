/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:31:11 by aromani           #+#    #+#             */
/*   Updated: 2025/04/22 02:11:12 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_putnbr(int n)
{
	char c;

	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
}

char	*get_token_type_str(t_token_type type)
{
	if (type == WORD)
		return ("WORD");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == REDIR_IN)
		return ("REDIR_IN");
	else if (type == REDIR_OUT)
		return ("REDIR_OUT");
	else if (type == APPEND)
		return ("APPEND");
	else if (type == HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}

#include <unistd.h>
#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	t_token	*current;
	int		i;

	current = tokens;
	i = 0;
	while (current)
	{
		write(1, "Token [", 7);
		ft_putnbr(i);
		write(1, "]:\n", 3);
		write(1, "  Type: ", 8);
		write(1, get_token_type_str(current->type),
			ft_strlen(get_token_type_str(current->type)));
		write(1, "\n", 1);
		write(1, "  Value: ", 9);
		if (current->value)
		{
			write(1, current->value, ft_strlen(current->value));
			write(1, "\n", 1);
		}
		else
			write(1, "(null)\n", 7);
		write(1, "----------------\n", 17);
		current = current->next;
		i++;
	}
}

int main(int ac, char **av)
{
	char *line;
	t_token *tokens;

	(void)av;
	tokens = NULL;
	if (ac != 1)
	{
		write(2, "Usage: ./minishell\n", 19);
		return (1);
	}
	setup_signals();
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			write(1, "\033[1A\033[2Kminishell> exit\n", 25);
			return (1);
		}
		if(line)
			add_history(line);
		tokens = ft_tokenization(line);
		if (validate_syntax(tokens))
		{
			print_syntax_error(tokens->value);
			ft_clear_tokens(&tokens);
			free(line);
			continue ;
		}
		print_tokens(tokens);
		ft_clear_tokens(&tokens);
		free(line);
	}
	return (0);
}

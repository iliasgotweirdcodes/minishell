/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:31:11 by aromani           #+#    #+#             */
/*   Updated: 2025/04/23 00:40:49 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

// int main(int ac,char **av)
// {
// 	// char *line;

// 	// setup_signals();
// 	// while (1)
// 	// {
// 	// 	line = readline("minishell> ");
// 	// 	if (!line)
// 	// 		break;
// 	// 	if (line[0] == '\0')
// 	// 	{
// 	// 		free(line);
// 	// 		continue;
// 	// 	}
// 	// 	printf("Input: %s\n", line);
// 	// 	// Parse the line into command + args
// 	// 	// execute the command
// 	// 	// free the command
// 	// 	free(line);
// 	// }
// 	t_command *cmd;
// 	(void)ac;
// 	cmd = malloc(sizeof(t_command));
// 	if (!cmd)
// 		return (0);
// 		//printf("%s \n", av[1]);
// 	cmd->prev = NULL;
// 	cmd->next = NULL;
// 	cmd->in_out = NULL;
// 	cmd->cmd = malloc(3 * sizeof(char *));
// 	cmd->cmd[0] = strdup(av[1]);
// 	cmd->cmd[1] = strdup(av[2]);
// 	cmd->cmd[2] = NULL;
// 	is_builtins(cmd);
void ft_putnbr(int n)
{
	char c;

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


int main(int ac , char **av)
{
	char	*input;
	t_token	*tokens;

	(void)av;
	if (ac != 1)
	{
		write(2, "Usage: ./minishell\n", 20);
		return (1);
	}
	setup_signals();
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			write(1, "\033[1A\033[2Kminishell> exit\n", 25);
			break ;
		}
		if (*input)
			add_history(input);
		tokens = ft_tokenization(input);
		if (!tokens)
		{
			ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
			free(input);
			continue ;
		}
		if (validate_syntax(tokens))
		{
			ft_clear_tokens(&tokens);
			free(input);
			continue ;
		}
		print_tokens(tokens);
		ft_clear_tokens(&tokens);
		free(input);
	}
	return (0);
}


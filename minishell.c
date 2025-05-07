/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:31:11 by aromani           #+#    #+#             */
/*   Updated: 2025/05/07 18:43:47 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status = 0;

int main(int ac , char **av, char **env)
{
	char	*input;
	t_token	*tokens = NULL;
	t_command	*cmd = NULL;
	t_gc 	*gc = NULL;
	t_gc 	*gc_env = NULL;
	t_env	*m_env = NULL;

	cmd = NULL;
	get_env(env, &m_env, &gc_env);
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
		if (input)
			add_history(input);
		tokens = ft_tokenization(input, &gc);
		expand_tokens(tokens, m_env, &gc);
		if (!tokens)
		{
			if (tokens == NULL && ft_strchr(input, '\''))
				ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
			else if (tokens == NULL && ft_strchr(input, '\"'))
				ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
			continue ;
		}
		if (validate_syntax(tokens))
			continue ;
		create_cmd_list(tokens, &cmd, &gc);
		cmd_execuiter(&cmd, &m_env, &gc);
		// ft_gcfree(&gc);
		// cmd = NULL;
	}
	return (0);
}


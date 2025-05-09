/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:31:11 by aromani           #+#    #+#             */
/*   Updated: 2025/05/09 20:31:25 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include <string.h>

int g_exit_status = 0;



int main(int ac , char **av, char **env)
{
	char	*input;
	t_token	*tokens = NULL;
	t_command	*cmd = NULL;
	t_gc 	*gc = NULL;
	t_gc 	*gc_exec = NULL;
	t_gc 	*gc_env = NULL;
	t_env	*m_env = NULL;

	// memset(cmd, 0, sizeof(t_command));
	get_env(env, &m_env, &gc_env);
	//execuiter function
	chell_lvlhandel(av, &m_env, &gc_exec);
	//mine
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
		// int i;
		// i = 0;
		
		// while (cmd)
		// {
		// 	while (cmd->cmd[i])
		// 		printf("%s  \n",cmd->cmd[i++]);
		// 	cmd = cmd->next;
		// }
		cmd_execuiter(&cmd, &m_env, &gc_exec);
		// res = get_valmustunseted(&m_env, &gc_exec);
		// int i = 0;
		// while (res && res[i])
		// 	printf("%s  \n",res[i++]);
		ft_gcfree(&gc);
		cmd = NULL;
		free(input);
	}
	return (0);
}


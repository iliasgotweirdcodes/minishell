/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:31:11 by aromani           #+#    #+#             */
/*   Updated: 2025/05/15 21:55:08 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include <string.h>

int g_exit_status = 0;

void print_command(t_command *cmd)
{
	while (cmd)
	{
		printf("---------------------------------------------\n");
		char **arr = cmd->cmd;
		char **in_out = cmd->in_out;
		int i = 0;
		int j = 0;
		while (arr && arr[i])
		{
			printf("Command[%d]: %s\n", i, arr[i]);
			i++;
		}
		while (in_out && in_out[j])
		{
			printf("In/Out[%d]: %s\n", j, in_out[j]);
			j++;
		}
		if (cmd->here_docfd != -1) {
			printf("Here_doc_fd: %d\n", cmd->here_docfd);
		}
		cmd = cmd->next;
		printf("---------------------------------------------\n");
	}
}
void f(){
	system("leaks minishell");
}

int main(int ac , char **av, char **env)
{
	char	*input;
	t_token	*tokens = NULL;
	t_command	*cmd = NULL;
	t_gc 	*gc = NULL;
	t_gc 	*gc_exec = NULL;
	t_gc 	*gc_env = NULL;
	t_env	*m_env = NULL;
	struct termios old_stdin;
	//atexit(f);


	// atexit(f);

	tcgetattr(1,&old_stdin);
	get_env(env, &m_env, &gc_env);
	//execuiter function
	param_adds(&m_env, &gc_env);
	shell_lvlhandle(av, &m_env, &gc_env);
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
			ft_gcfree(&gc_env);
			break ;
		}
		if (input)
			add_history(input);
		tokens = parse_cmd(input, m_env, &gc);
		create_cmd_list(tokens, &cmd, &gc);
		//print_command(cmd);
		pwd_set(&cmd, &m_env, &gc_exec);
		g_exit_status = cmd_execuiter(&cmd, &m_env, &gc_exec, &gc_env);
		// res = get_valmustunseted(&m_env, &gc_exec);
		// int i = 0;
		// while (res && res[i])
		// 	printf("%s  \n",res[i++]);
		tcsetattr(1,0,&old_stdin);
		ft_gcfree(&gc);
		ft_gcfree(&gc_exec);
		cmd = NULL;
		free(input);
	}
	return (g_exit_status);
}


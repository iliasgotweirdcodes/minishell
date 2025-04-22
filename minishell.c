/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:31:11 by aromani           #+#    #+#             */
/*   Updated: 2025/04/21 23:59:49 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

int main(int ac,char **av)
{
	// char *line;

	// setup_signals();
	// while (1)
	// {
	// 	line = readline("minishell> ");
	// 	if (!line)
	// 		break;
	// 	if (line[0] == '\0')
	// 	{
	// 		free(line);
	// 		continue;
	// 	}
	// 	printf("Input: %s\n", line);
	// 	// Parse the line into command + args
	// 	// execute the command
	// 	// free the command
	// 	free(line);
	// }
	t_command *cmd;
	(void)ac;
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (0);
		//printf("%s \n", av[1]);
	cmd->prev = NULL;
	cmd->next = NULL;
	cmd->in_out = NULL;
	cmd->cmd = malloc(3 * sizeof(char *));
	cmd->cmd[0] = strdup(av[1]);
	cmd->cmd[1] = strdup(av[2]);
	cmd->cmd[2] = NULL;
	is_builtins(cmd);
	return (0);
}

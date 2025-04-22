/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:03:56 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/04/21 22:00:38 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>

# include "readline/readline.h"
# include "readline/history.h"


typedef struct s_command {
	struct s_command *prev; // Pointer to the previous command in the pipeline
    char **cmd;     // Actual command and its arguments
    char **in_out;   // Redirections and tokens
	struct s_command *next; // Pointer to the next command in the pipeline
} t_command;

typedef struct s_shell {
	char *line; // The input line from the user
	t_command *cmd; // Pointer to the first command in the pipeline
} t_shell;

void	setup_signals(void);

// test for execuition builtins 
void is_builtins(t_command *cmd);
int	ft_strcmp(const char *s1, const char *s2);
void ft_putstr(char *str);

#endif

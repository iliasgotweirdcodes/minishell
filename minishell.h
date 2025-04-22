/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:03:56 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/04/22 11:49:16 by aromani          ###   ########.fr       */
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
#include <stddef.h>

# include "readline/readline.h"
# include "readline/history.h"

typedef enum e_token_type {
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	LEFT_PAREN,
	RIGHT_PAREN,
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
} t_token_type;

typedef struct s_env
{
	char **env;
}	t_env;

typedef struct s_token {
	t_token_type type; // Type of the token (e.g., WORD, PIPE, etc.)
	char *value;       // The actual string value of the token
	struct s_token *next; // Pointer to the next token in the list
	struct s_token *prev; // Pointer to the previous token in the list
} t_token;

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



t_token	*ft_tokenization(char *input);
void	ft_add_token(t_token **token_list, t_token *new_token);
t_token	*ft_create_token(t_token_type type, char *value);
void	ft_clear_tokens(t_token **token_list);
char	*ft_strndup(const char *s, size_t n);
void	ft_error(char *msg);
int		ft_strlen(char *str);
int		is_operator(char c);
int		is_quote(char c);
int		is_space(char c);
int		validate_syntax(t_token *tokens);
void	print_syntax_error(char *token);
int	is_redirection(t_token_type type);

#endif

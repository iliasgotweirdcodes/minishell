/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:45:36 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/04/23 22:02:18 by aromani          ###   ########.fr       */
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
    char        *key;  // env param
    char        *value; // env value
    struct s_env *next;
} t_env;

// gc linked list
typedef struct gc
{
	void *address;
	struct gc *next;
}	t_gc;

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
	int here_docfd;   // for the heredoc fd
	struct s_command *next; // Pointer to the next command in the pipeline
} t_command;

typedef struct s_shell {
	char *line; // The input line from the user
	t_command *cmd; // Pointer to the first command in the pipeline
} t_shell;

void	setup_signals(void);

//execuition
void is_builtins(t_command *cmd);
char    *ft_strdup2(const char *s, t_gc **exec);
char	*last_path(char **env, char **arg);
char    *ft_strndup2(const char *s, size_t n, t_gc **exec);
int get_eqindex(char *str, char sep);
void	env_fill(t_env **env, char **key, char **val, t_gc **exec);
void	add_varenv(t_env **env, char *key_val, t_gc **exec);
char	*ft_strjoinv3(char *s1, char*s2,t_gc **exec);


//parsing
t_token	*ft_tokenization(char *input);
void	ft_add_token(t_token **token_list, t_token *new_token);
t_token	*ft_create_token(t_token_type type, char *value);
void	ft_clear_tokens(t_token **token_list);
char	*ft_strndup(const char *s, size_t n);
void	ft_error(char *msg);
int		ft_strlen(char *str);
int		is_operator(t_token_type type);
int		is_quote(char c);
int		is_space(char c);
int		validate_syntax(t_token *tokens);
void	print_syntax_error(t_token *token);
void	print_quote_error(void);
int		is_space(char c);
int		is_redirection(t_token_type type);
void	print_quote_error(void);
void ft_putstr_fd(char *str, int fd);
char	*ft_strchr(const char *s, int c);


//Garbage collector
//void	ft_addnew(t_gc **gc, void * add);
//t_gc	*struct_fill(t_gc *gc, void * add);
void *ft_malloc(size_t size, t_gc **gc);
void ft_gcfree(t_gc **gc);
void ft_putstr(char *str);
int	ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(char *str);
char	*ft_substr(char *s, int start, int end);

// general purpose



#endif

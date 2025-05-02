/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:45:36 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/05/02 02:58:09 by aromani          ###   ########.fr       */
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
#include <termios.h>

# include "readline/readline.h"
# include "readline/history.h"

typedef enum e_token_type {
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
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
	struct s_token *prev; // Pointer to the previous token in the list
	char *value; // The actual string value of the token
	struct s_token *next; // Pointer to the next token in the list
	int here_docfd; // for the heredoc fd
} t_token;

typedef struct s_command {
	struct s_command *prev; // Pointer to the previous command in the pipeline
    char **cmd;     // Actual command and its arguments
    char **in_out;   // Redirections and tokens
	int here_docfd;   // for the heredoc fd
	t_env **env_ptr;   //for holding the env pointer norminet
	struct s_command *next; // Pointer to the next command in the pipeline
} t_command;


void	setup_signals(void);

//execution
int is_builtinns(t_command *cmd);
char    *ft_strdup2(const char *s, t_gc **exec);
char	*last_path(char **env, char **arg, t_gc **exec);
char	*path_geter(char *str, char **ev);
char    *ft_strndup2(const char *s, size_t n, t_gc **exec);
int get_eqindex(char *str, char sep);
void	env_fill(t_env **env, char **key, char **val, t_gc **exec);
int	add_varenv(t_env **env, char *key_val, t_gc **exec);
char	*ft_strjoinv3(char *s1, char*s2,t_gc **exec);
char **env_converter(t_env **env,t_gc **exec);
void get_env(char **env, t_env **my_env, t_gc **exec);
void cd_builtins(char *path, t_env **s_env, t_gc **exec);
void echo_builtind(t_command *cmd);
int export(t_env **my_env, t_command **cmd, t_gc **exec);
 //int export(t_env **my_env, t_command **cmd, t_gc **exec);
//int export(t_env **my_env, t_command **cmd, t_gc **exec, char **env);
void env_builtins(t_env **my_env, t_gc **gc);
//void env_builtins(char **my_env, t_gc **gc);
void pwd_builtins(void);
void    unset_builtins(t_env **env, char *key);
void exit_builtins(t_gc **gc);
void single_command(t_command **cmd, char **env, t_gc **exec);
void cmd_execuiter(t_command **cmd_list, t_env **env, t_gc **exec);
void redirection_handel(t_command **t_cmd);
void multi_cmd(char **env, t_command **cmd,t_gc **exec);
void builtins_execuition(t_command **cmd, t_env **env, t_gc **exec);


//parsing
t_token *ft_tokenization(char *input, t_gc **gc);
void	ft_add_token(t_token **token_list, t_token *new_token);
t_token	*ft_create_token(t_token_type type, char *value , t_gc **gc);
// void	ft_clear_tokens(t_token **token_list);
char	*ft_strndup(const char *s, size_t n, t_gc **gc);
void	ft_error(char *msg);
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
int	hanlde_here_doc(char *delimiter);
void	prepare_cmd(t_command **cmd, t_token *tokens, t_gc **gc);
void prepare_in_out(t_command **cmd, t_token *tokens , t_gc **gc);

//expansion
void	expand_tokens(t_token *tokens, t_env *env, t_gc **gc);


// list tools
t_command	*ft_lstnew(char **content, t_gc **gc);
// void	ft_lstadd_back(t_command **lst, t_command *new);
// t_command	*ft_lstlast(t_command *lst);
// void	ft_lstclear(t_command **lst, void (*del)(void*));

//Garbage collector
//void	ft_addnew(t_gc **gc, void * add);
//t_gc	*struct_fill(t_gc *gc, void * add);
void *ft_malloc(size_t size, t_gc **gc);
void ft_gcfree(t_gc **gc);

// general purpose
void ft_putstr(char *str);
int	ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(char *str, t_gc **gc);
char	*ft_substr(char *s, int start, size_t len, t_gc **gc);
size_t	ft_strlen(char *str);
char	**ft_split(char *s, char c , t_gc **gc);
char	*ft_strjoin(char *s1, char *s2, t_gc **gc);
int	ft_isalnum(int c);

#endif

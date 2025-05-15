/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:45:36 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/05/15 21:41:38 by ilel-hla         ###   ########.fr       */
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
#include <sys/types.h>
#include <dirent.h>
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

extern int g_exit_status; // Global variable to hold the exit status

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
	char *oldpwd_set; // holdind the old pwd
	char *pwd_sec;  // hlding the pwd
	struct s_command *next; // Pointer to the next command in the pipeline
} t_command;



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
int cd_builtins(t_command **cmd, char *path, t_env **s_env, t_gc **exec);
int echo_builtind(t_command **cmd);
int export(t_env **my_env, t_command **cmd, t_gc **exec);
int env_builtins(t_env **my_env);
int pwd_builtins(t_env **env);
void ft_changeval(t_env **env, char *key_val, t_gc **exec);
int    unset_builtins(t_env **my_env, t_command **cmd, t_gc **exec);
int    unset_management(t_env **env, char *key, t_gc **exec);
int exit_builtins(t_command **cmd,t_gc **exec_gc, t_gc **env_gc);
// int single_command(t_command **cmd, char **env, t_gc **exec);
// int single_command(t_command **cmd, char **env, t_gc **env_gc);
int single_command(t_command **cmd, t_gc **exec_gc, t_gc **env_gc, t_env **s_env);
int cmd_execuiter(t_command **cmd_list, t_env **env, t_gc **exec, t_gc **env_gc);
int redirection_handel(t_command **t_cmd);
int multi_cmd(t_command **cmd,t_gc **exec, t_env **s_env, t_gc **env_gc);
int builtins_execuition(t_command **cmd, t_env **env, t_gc **exec, t_gc **gc_env);
int is_key(t_env **env, char *key_val, t_gc **exec);
// char	*ft_itoa(int nbr);
void chell_lvlhandel(char **cmd,t_env **env, t_gc **gc);
//char ** get_valmustunseted(t_env **env, t_gc **exec);
int sep_exist(char *str, char sep);
void error_printer(char *str, char* message, char *name);
int export_parser(char *str, t_gc **exec);
int	ft_isalpha(int c);
int	ft_isalnum(int c);
int	ft_isdigit(int c);
int	ft_revsrch(const char *s, int c);
char	*ft_strjoinv2(char *s1, char *s2, t_gc **exec);
void pwd_set(t_command **cmd, t_env **env, t_gc **gc_exec);
void param_adds(t_env **s_env, t_gc **env_gc);
int cmd_sizer(t_command *cmd);
int is_inparent(t_command *cmd);

//parsing
void	setup_signals(void);
t_token *ft_tokenization(char *input, t_gc **gc);
void	ft_add_token(t_token **token_list, t_token *new_token);
t_token	*ft_create_token(t_token_type type, char *value , t_gc **gc);
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
char	*ft_strchr(const char *s, int c);
int		hanlde_here_doc(char *delimiter);
char	**prepare_cmd(t_token *tokens, t_gc **gc);
char	*get_cmd(t_token *tokens, t_gc **gc);
char	**prepare_in_out(t_token *tokens , t_gc **gc);
char	*get_env_value(char *var_name, t_env *env);
void	sigint_handler(int sig);
t_token	*parse_cmd(char *input, t_env *m_env, t_gc **gc);
char	**ft_split_quotes(char *s, t_gc **gc);
void	expand_tokens(t_token **tokens, t_env *env, t_gc **gc);
char	*get_env_value(char *var_name, t_env *env);
char	*ft_charjoin(char *str, char c, t_gc **gc);
char	*ft_remove_quotes(char *str, t_gc **gc);
void	remove_quotes(char **str, t_gc **gc);
void	create_cmd_list(t_token *tokens , t_command **cmd_list, t_gc **gc);

//Garbage collector
void	*ft_malloc(size_t size, t_gc **gc);
void	ft_gcfree(t_gc **gc);
void	ft_lstclear(t_command **lst, t_gc **gc);

// general purpose
void	ft_putstr(char *str);
void	ft_putstr_fd(char *str, int fd);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(char *str, t_gc **gc);
char	*ft_substr(char *s, int start, size_t len, t_gc **gc);
size_t	ft_strlen(char *str);
char	**ft_split(char *s, char c , t_gc **gc);
char	*ft_strjoin(char *s1, char *s2, t_gc **gc);
int		ft_isalnum(int c);
char	*ft_strtrim(char *s1, char const *set, t_gc **gc);
char	*ft_itoa(int n, t_gc **gc);
char	**ft_split_vtab(char *s, t_gc **gc);

#endif

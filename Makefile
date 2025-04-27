NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
READLINE_COMPILE = -I$(shell brew --prefix readline)/include
READLINE_LINK = -L$(shell brew --prefix readline)/lib -lreadline -lhistory


SRC =  minishell.c parsing/signal.c parsing/tokenization.c parsing/token_utils.c parsing/helpers.c \
		parsing/error.c parsing/syntax_error.c parsing/syntax_utils.c execution/builtins_handle.c execution/builtins/utils/utils_01.c \
		parsing/here_doc.c parsing/list_tools.c parsing/prepare_of_cmd.c parsing/ft_split.c parsing/ft_strjoin.c \
		execution/environment/get_env.c gc/ft_malloc.c execution/builtins/cd.c execution/environment/env_manager.c execution/builtins/echo.c \
		execution/builtins/export.c execution/builtins/env.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(READLINE_LINK) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(READLINE_COMPILE) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all


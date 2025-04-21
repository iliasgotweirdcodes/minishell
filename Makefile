NAME = Minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = main.c \
		env.c \
		builtins.c \
		builtins_cd.c \
		builtins_echo.c \
		builtins_env.c \
		builtins_exit.c \
		builtins_export.c \
		builtins_pwd.c \
		builtins_unset.c \
		exec_cmds.c \
		exec_utils.c \
		parsing.c \
		parsing_utils.c \
		signal_handler.c \

OBJS = $(SRCS:.c=.o)


tstts = tetsts.h

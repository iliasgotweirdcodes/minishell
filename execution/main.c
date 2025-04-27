#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void is_builtin(t_command *cmd)
{
    char *str;
    t_command *tmp;

    tmp = cmd;
    while (tmp != NULL)
    {
        if (ft_strcmp(tmp->cmd[0] ,"pwd") == 0)
        {
            str = getcwd(NULL, 0);
            if (!str)
                return (perror ("getcwd() error"), exit(1));
            ft_putstr(str);
            ft_putstr("\n");
        }
        // else if (ft_strcmp(tmp->cmd[0] ,"cd") == 0)
        // {
        //     if (chdir(tmp->cmd[1]) == -1)
        //         return (perror ("chdir() error"), exit(1));
        // }
        tmp = tmp->next;
    }
} 

void free_command_list(t_command *cmd) {
	while (cmd) {
		t_command *next = cmd->next;

		if (cmd->cmd) {
			for (int i = 0; cmd->cmd[i]; i++)
				free(cmd->cmd[i]);
			free(cmd->cmd);
		}

		if (cmd->in_out) {
			for (int i = 0; i < 3 && cmd->in_out[i]; i++)
				free(cmd->in_out[i]);
			free(cmd->in_out);
		}

		free(cmd);
		cmd = next;
	}
}



char *get_line(const char *prompt) {
    char *line = readline(prompt);
    if (!line) {
        printf("exit\n"); // Bash-like behavior on Ctrl+D
        return NULL;
    }
    if (*line)
        add_history(line);
    return line;
}

char **get_command_args() {
    char **args = malloc(sizeof(char *) * 100);
    int i = 0;
    char *input = get_line("Command (e.g. ls): ");
    if (!input) {
        free(args);
        return NULL;
    }
    args[i++] = input;

    while (1) {
        char prompt[64];
        sprintf(prompt, "Argument #%d (or just ENTER to skip): ", i);
        char *arg = get_line(prompt);
        if (!arg || strlen(arg) == 0) {
            free(arg);
            break;
        }
        args[i++] = arg;
    }
    args[i] = NULL;
    return args;
}

char **get_redirection() {
    char **redir = calloc(4, sizeof(char *));
    redir[0] = get_line("Redirection (<, >, >>, << or ENTER to skip): ");
    if (!redir[0]) {
        free(redir);
        return NULL;
    }

    if (strlen(redir[0]) > 0) {
        if (strcmp(redir[0], "<") == 0)
            redir[2] = strdup("in");
        else if (strcmp(redir[0], ">") == 0 || strcmp(redir[0], ">>") == 0)
            redir[2] = strdup("out");
        else if (strcmp(redir[0], "<<") == 0)
            redir[2] = strdup("heredoc");
        else {
            printf("Invalid redirection operator.\n");
            free(redir[0]);
            free(redir);
            return NULL;
        }

        redir[1] = get_line(strcmp(redir[2], "heredoc") == 0 ?
                            "Here-document delimiter: " : "Redirection file: ");
        if (!redir[1]) {
            free(redir[0]);
            free(redir[2]);
            free(redir);
            return NULL;
        }
    } else {
        free(redir[0]);
        redir[0] = NULL;
    }

    return redir;
}

t_command *create_command() {
    t_command *cmd = calloc(1, sizeof(t_command));
    cmd->cmd = get_command_args();
    if (!cmd->cmd) {
        free(cmd);
        return NULL;
    }

    cmd->in_out = get_redirection();
    return cmd;
}

t_command *build_command_list() {
    t_command *head = NULL;
    t_command *prev = NULL;
    int index = 1;

    while (1) {
        printf("\n--- Command #%d ---\n", index++);
        t_command *cmd = create_command();
        if (!cmd)
            break;

        if (!head)
            head = cmd;
        if (prev) {
            prev->next = cmd;
            cmd->prev = prev;
        }
        prev = cmd;

        char *more = get_line("Add a pipe to another command? (y/n): ");
        if (!more || strcmp(more, "y") != 0) {
            free(more);
            break;
        }
        free(more);
    }
    return head;
}

int main(int argc, char *argv[], char **env) {
    (void)argc;
    (void)argv;
    t_gc *gc = NULL;
    t_env *env_struct = NULL;

    get_env(env, &env_struct, &gc);
    // while (env_struct)
    // {
    //     printf("%s --------- %s\n", env_struct->key,env_struct->value);
    //     env_struct = env_struct->next;
    // }
   //return 0;
    while (1) {
        t_command *cmd_list = build_command_list();
        if (!cmd_list)
            break;

        if (!cmd_list->cmd || !cmd_list->cmd[0]) {
            free_command_list(cmd_list);
            continue;
        }
        if (strcmp(cmd_list->cmd[0], "exit") == 0) {
            free_command_list(cmd_list);
            printf("Bye 👋\n");
            break;
        }
        //printf("<<<<<<<<<<<<%s>>>>>>>>>>>>",cmd_list->cmd[1]);
        // cd_builtins(cmd_list->cmd[1],&env_struct,&gc);
        //echo_builtind(cmd_list);
        // excute the command
        export(&env_struct,&cmd_list,&gc);
        char **ma_env = env_converter(&env_struct,&gc);
        env_builtins(ma_env);
        //is_builtin(cmd_list);
        free_command_list(cmd_list); 
    }

    return 0;
}

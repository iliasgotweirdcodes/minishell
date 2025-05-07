/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:15:29 by aromani           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/07 19:58:02 by ilel-hla         ###   ########.fr       */
=======
/*   Updated: 2025/05/07 18:56:27 by aromani          ###   ########.fr       */
>>>>>>> 66e3f7ecccf141143a261c02de9d27d3ea8ad006
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fcheck(char *av)
{
	int	fd;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (0);
	return (close(fd), 1);
}

// char *cmd_converter(t_command **cmd_list, t_gc **gc)
// {
//     char *new_cmd;
//     int i;
//     t_command *cmd;

//     cmd = *cmd_list;
//     i = 0;
//     while (cmd)
//     {
//         if (!new_cmd)
//         {
//             new_cmd = ft_strdup2("", gc);
//             if (!new_cmd)
//                 return (NULL);
//         }
//         while (cmd->in_out[i])
//         {
//             new_cmd = ft_strjoinv3(new_cmd, cmd->in_out[i], gc);
//             if (!new_cmd)
//                 return (NULL);
//         }
//         cmd = cmd->next;
//     }
//     return (new_cmd);
// }

int keyred_counter(char **cmd)
{
    int i;
    int c;

    c = 0;
    i = 0;
    while (cmd[i])
    {
        if (ft_strcmp(cmd[i], "<") == 0 || ft_strcmp(cmd[i], ">") == 0 ||
            ft_strcmp(cmd[i], "<<") == 0 || ft_strcmp(cmd[i], ">>") == 0)
                c++;
        i++;
    }
    return (c);
}

void error_printer(char *str)
{
    write(2, "minishell: ", 11);
    perror(str);
}

void redirection_handel(t_command **t_cmd)
{
    int i;
    int red_in;
    int red_out;
    t_command *tmp;

    i = 0;
    red_out = -2;
    red_in = -2;
    tmp = *t_cmd;
    while (tmp->in_out && tmp->in_out[i])
    {
        if (ft_strcmp(tmp->in_out[i],"<") == 0)
        {
            if(red_in != -2)
                close(red_in);
            red_in = open(tmp->in_out[i + 1], O_RDONLY);
            if (red_in == -1)
                return (error_printer (tmp->in_out[i + 1]));
        }
        else if (ft_strcmp(tmp->in_out[i],">") == 0)
        {
            if (red_out != -2)
                close(red_out);
            red_out = open(tmp->in_out[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if (!red_in)
                return (error_printer (tmp->in_out[i + 1]));
        }
        else if (ft_strcmp(tmp->in_out[i], ">>") == 0)
        {
            if (red_out != -2)
                close(red_out);
            red_out = open(tmp->in_out[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
            if (red_out == -1)
                return (error_printer (tmp->in_out[i + 1]));
        }
        else if (ft_strcmp(tmp->in_out[i], "<<") == 0)
        {
             if(red_in != -2)
                close(red_in);
            red_in = tmp->here_docfd;
            if (red_in == -1)
                return (error_printer (tmp->in_out[i + 1]));
        }
        i++;
    }
    if (red_in != -2)
    {
        printf("ana fd n : %d dapeet fe 0\n",red_in);
        dup2(red_in, 0);
        close(red_in);
    }
    if (red_out != -2)
    {
        printf("ana fd n : %d dapeet fe 1\n",red_out);
        dup2(red_out, 1);
        close(red_out);
    }
<<<<<<< HEAD
    // (void)heredoc_fd;
    // // j = 0;
    // // while ((*t_cmd)->in_out[j])
    // // {
    // red_count = keyred_counter((*t_cmd)->in_out);
    // // }
    // printf("%s \n", (*t_cmd)->in_out[i]);
    // while ((*t_cmd)->in_out[i])
    // {
    //     if (ft_strcmp((*t_cmd)->in_out[i], "<"))
    //     {
    //         if (fcheck((*t_cmd)->in_out[i + 1]) == 1)
    //             dup2(fd, 0);
    //     }
    //     if (ft_strcmp((*t_cmd)->in_out[i], ">"))
    //     {
    //         fd = open((*t_cmd)->in_out[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
    //          if (fd == -1)
    //             return ;
    //         dup2(fd, 1);
    //         close(fd);
    //     }
    //     else if (ft_strcmp((*t_cmd)->in_out[i], "<<") == 0)
    //         dup2(heredoc_fd, 0);
    //     i++;
    // }
=======
>>>>>>> 66e3f7ecccf141143a261c02de9d27d3ea8ad006
}

void chell_lvlhandel(char **cmd,t_env **env, t_gc **gc)
{
    int val = 0;
    char *new_val = NULL;
    char *key;

    if (ft_strcmp(cmd[0], "./minishell") == 0)
    {
        key = get_env_value("SHLVL",*env);
        if (key)
            val = atoi(key);
        if (val < 0)
            val = 0;
        if (val > 999)
            val = 1;
        val++;
        new_val = ft_strjoinv3("SHLVL=", ft_itoa(val), gc);
        ft_changeval(env, new_val, gc);
    }
}
int single_command(t_command **cmd, char **env, t_gc **exec, t_env **m_env)
{
    pid_t id;
    char *path;

    if (!(*cmd)->cmd)
    {
        redirection_handel(cmd);
        return (0);
    }
    path = last_path(env, (*cmd)->cmd, exec);
    if (!path)
    {
        printf("minishell: %s: command not found\n",(*cmd)->cmd[0]);
        return (1);
    }
    //need too delete it
    (void)m_env;
    // if (ft_strcmp(path, "./minishell") == 0)
    // {
    //     chell_lvlhandel(m_env, exec);
    //     //printf("%s  \n",path);
    // }
    id = fork();
    if (id < 0)
        return (perror(""), exit(1), 1);
    if (id == 0)
    {
        redirection_handel(cmd);
        if (execve(path, (*cmd)->cmd, env) == -1)
        {
            perror("execve :");
            exit(1);
        }
    }
    // while (wait(0) != -1)
    //     ;
    return (0);
}

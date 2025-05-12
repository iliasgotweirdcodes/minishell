/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:01:13 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/05/12 16:32:22 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_shell_operator(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

int handle_operator(char *input, int i, t_token **token_list, t_gc **gc)
{
    if (input[i] == '|')
    {
        ft_add_token(token_list, ft_create_token(PIPE, NULL, gc));
        i++;
    }
    else if (input[i] == '<' && input[i + 1] == '<')
    {
        ft_add_token(token_list, ft_create_token(HEREDOC, NULL, gc));
        i += 2;
    }
    else if (input[i] == '>' && input[i + 1] == '>')
    {
        ft_add_token(token_list, ft_create_token(APPEND, NULL, gc));
        i += 2;
    }
    else if (input[i] == '<')
    {
        ft_add_token(token_list, ft_create_token(REDIR_IN, NULL, gc));
        i++;
    }
    else if (input[i] == '>')
    {
        ft_add_token(token_list, ft_create_token(REDIR_OUT, NULL, gc));
        i++;
    }
    return (i);
}

int handle_word(char *input, int i, t_token **token_list, t_gc **gc)
{
    int start = i;
    char quote = 0;
    char *value;

    while (input[i] && (quote || (!is_space(input[i]) && !is_shell_operator(input[i]))))
    {
        if ((input[i] == '\'' || input[i] == '"') && !quote)
            quote = input[i++];
        else if (input[i] == quote)
        {
            quote = 0;
            i++;
        }
        else
            i++;
    }
    if (quote)
        return (-1);
    value = ft_strndup(input + start, i - start, gc);
    if (!value)
    {
        // ft_clear_tokens(token_list);
        return (-1);
    }
    ft_add_token(token_list, ft_create_token(WORD, value, gc));
    return (i);
}

t_token *ft_tokenization(char *input, t_gc **gc)
{
    t_token *token_list;
    int     i;

    token_list = NULL;
    i = 0;
    while (input[i])
    {
        while (input[i] == ' ' || input[i] == '\t')
            i++;
        if (!input[i])
            break ;
        if (is_shell_operator(input[i]))
            i = handle_operator(input, i, &token_list, gc);
        else
        {
            i = handle_word(input, i, &token_list, gc);
            if (i == -1)
                return (NULL);
        }
    }
    return (token_list);
}

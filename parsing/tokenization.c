/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:01:13 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/04/25 18:56:07 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_shell_operator(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

int handle_operator(char *input, int i, t_token **token_list)
{
    if (input[i] == '|')
    {
        ft_add_token(token_list, ft_create_token(PIPE, NULL));
        i++;
    }
    else if (input[i] == '<' && input[i + 1] == '<')
    {
        ft_add_token(token_list, ft_create_token(HEREDOC, NULL));
        i += 2;
    }
    else if (input[i] == '>' && input[i + 1] == '>')
    {
        ft_add_token(token_list, ft_create_token(APPEND, NULL));
        i += 2;
    }
    else if (input[i] == '<')
    {
        ft_add_token(token_list, ft_create_token(REDIR_IN, NULL));
        i++;
    }
    else if (input[i] == '>')
    {
        ft_add_token(token_list, ft_create_token(REDIR_OUT, NULL));
        i++;
    }
    return (i);
}

int handle_word(char *input, int i, t_token **token_list)
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
    value = ft_strndup(input + start, i - start);
    if (!value)
    {
        ft_clear_tokens(token_list);
        return (-1);
    }
    ft_add_token(token_list, ft_create_token(WORD, value));
    return (i);
}

t_token *ft_tokenization(char *input)
{
    t_token *token_list = NULL;
    int i = 0;
    int error = 0;

    while (input[i] && !error)
    {
        while (input[i] == ' ')
            i++;
        if (!input[i])
            break;
        if (is_shell_operator(input[i]))
            i = handle_operator(input, i, &token_list);
        else
        {
            int new_i = handle_word(input, i, &token_list);
            if (new_i == -1)
                error = 1;
            else
                i = new_i;
        }
    }
    if (error)
    {
        ft_clear_tokens(&token_list);
        return (NULL);
    } 
    return (token_list);
}

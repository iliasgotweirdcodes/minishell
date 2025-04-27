/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:24:45 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/04/27 16:48:35 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char	*get_env_value(char *var_name, t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, var_name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
char	*handle_dollar(char *value, int *i, t_env *env, char *res)
{
	int		start;
	char	*var_name;
	char	*var_value;

	start = ++(*i);
	while (value[*i] && (ft_isalnum(value[*i]) || value[*i] == '_'))
		(*i)++;
	var_name = ft_substr(value, start, *i - start);
	if (!var_name)
		return (NULL);
	var_value = get_env_value(var_name, env);
	free(var_name);
	return (ft_strjoin(res, var_value));
}

t_token_type	get_quote_state(t_token *token)
{
	while (token && token->type != DOUBLE_QUOTE && token->type != SINGLE_QUOTE)
		token = token->prev;
	if (!token)
		return (WORD);
	return (token->type);
}
char	*append_char(char *str, char c)
{
	char	*new_str;
	int		len;
	int		i;

	if (!str)
	{
		new_str = malloc(2);
		if (!new_str)
			return (NULL);
		new_str[0] = c;
		new_str[1] = '\0';
		return (new_str);
	}
	len = ft_strlen(str);
	new_str = malloc(len + 2);
	if (!new_str)
		return (NULL);
	i = -1;
	while (++i < len)
		new_str[i] = str[i];
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(str);
	return (new_str);
}

char	*expand_variable(char *value, t_env *env, t_token *token)
{
	char		*result;
	int			i;
	t_token_type	quote_state;

	result = NULL;
	quote_state = get_quote_state(token);
	i = 0;
	while (value[i])
	{
		if (value[i] == '$' && quote_state != SINGLE_QUOTE)
		{
			result = handle_dollar(value, &i, env, result);
			if (!result)
				return (NULL);
		}
		else
		{
			result = append_char(result, value[i]);
			i++;
		}
		if (!result)
			break ;
	}
	return (result);
}

void	expand_tokens(t_token *tokens, t_env *env)
{
	t_token	*current;
	char	*expanded;

	current = tokens;
	while (current)
	{
		if (current->type == WORD)
		{
			expanded = expand_variable(current->value, env, current);
			if (expanded)
			{
				free(current->value);
				current->value = expanded;
			}
		}
		current = current->next;
	}
}

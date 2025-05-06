/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:32:54 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/05/04 17:41:27 by ilel-hla         ###   ########.fr       */
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

char	*append_char(char *str, char c, t_gc **gc)
{
	char	*new_str;
	int		len;
	int		i;

	if (!str)
	{
		new_str = ft_malloc(2, gc);
		if (!new_str)
			return (NULL);
		new_str[0] = c;
		new_str[1] = '\0';
		return (new_str);
	}
	len = ft_strlen(str);
	new_str = ft_malloc(len + 2, gc);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}

char	*handle_dollar(char *value, int *i, t_env *env, char *res, t_gc **gc)
{
	int		start;
	char	*var_name;
	char	*var_value;
	char	*new_res;

	start = ++(*i);
	while (value[*i] && (ft_isalnum(value[*i]) || value[*i] == '_'))
		(*i)++;
	var_name = ft_substr(value, start, *i - start, gc);
	if (!var_name)
		return (NULL);
	var_value = get_env_value(var_name, env);
	if (!var_value)
		var_value = "";
	new_res = ft_strjoin(res, var_value, gc);
	return (new_res);
}

char	*process_quotes_and_vars(char *value, t_env *env, t_gc **gc)
{
	char	*result;
	int		i;
	int		quote;

	result = NULL;
	i = 0;
	quote = 0;
	while (value[i])
	{
		if (value[i] == '\'' && quote != 2)
		{
			if (quote == 1)
				quote = 0;
			else
				quote = 1;
			i++;
		}
		else if (value[i] == '"' && quote != 1)
		{
			if (quote == 2)
				quote = 0;
			else
				quote = 2;
			i++;
		}
		else if (value[i] == '$' && quote != 1)
		{
			result = handle_dollar(value, &i, env, result, gc);
			if (!result)
				break ;
		}
		else
		{
			result = append_char(result, value[i], gc);
			i++;
		}
	}
	return (result);
}

char	*expand_variable(char *value, t_env *env, t_gc **gc)
{
	char	*expanded;
	int		quote_type;
	char	*temp;

	quote_type = 0;
	if (value[0] == '"' && value[ft_strlen(value) - 1] == '"')
		quote_type = 2;
	else if (value[0] == '\'' && value[ft_strlen(value) - 1] == '\'')
		quote_type = 1;
	expanded = process_quotes_and_vars(value, env, gc);
	if (quote_type == 1)
		temp = ft_strtrim(expanded, "'", gc);
	else if (quote_type == 2)
		temp = ft_strtrim(expanded, "\"", gc);
	else
		temp = ft_strdup(expanded, gc);
	return (temp);
}

void	expand_tokens(t_token *tokens, t_env *env, t_gc **gc)
{
	t_token	*current;
	char	*expanded;

	current = tokens;
	while (current)
	{
		if (current->type == WORD)
		{
			expanded = expand_variable(current->value, env, gc);
			if (expanded)
				current->value = expanded;
		}
		current = current->next;
	}
}

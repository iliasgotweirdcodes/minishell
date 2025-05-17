/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:32:54 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/05/17 18:18:52 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_dollar(char *str, int *i, t_env *env, t_gc **gc)
{
	int		start;
	int		len;
	char	*var;
	char	*val;

	(*i)++;
	start = *i;
	len = 0;
	if (str[start] == '?')
	{
		(*i)++;
		return(ft_strdup(ft_itoa(0, gc), gc));
	}
	if (str[start] == '$')
	{
		(*i)++;
		return (ft_strdup("$", gc));
	}
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
	{
		(*i)++;
		len++;
	}
	var = ft_substr(str, start, len, gc);
	val = get_env_value(var, env);
	return (ft_strdup(val, gc));
}

char	*expand_variable(char *value, t_env *env, t_gc **gc)
{
	char	*result;
	int		i;
	int		quote;
	char	*expanded;

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
			result = ft_charjoin(result, value[i], gc);
			i++;
		}
		else if (value[i] == '\"' && quote != 1)
		{
			if (quote == 2)
				quote = 0;
			else
				quote = 2;
			result = ft_charjoin(result, value[i], gc);
			i++;
		}
		else if (value[i] == '$' && quote != 1)
		{
			expanded = expand_dollar(value, &i, env, gc);
			result = ft_strjoin(result, expanded, gc);
		}
		else
		{
			result = ft_charjoin(result, value[i], gc);
			i++;
		}
	}
	return (result);
}

void	expand_tokens(t_token **tokens, t_env *env, t_gc **gc)
{
	t_token	*current;
	char	*expanded;

	current = *tokens;
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

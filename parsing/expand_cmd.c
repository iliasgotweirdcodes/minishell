/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:32:54 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/05/15 22:07:10 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char    *handle_dollar(char *value, int *i, t_env *env, char *res, t_gc **gc)
// {
//     int     start;
//     char    *var_name;
//     char    *var_value;
//     char    *new_res;

//     start = ++(*i);
//     if (value[start] == '?')
//     {
//         var_name = ft_strdup("?", gc);
//         (*i)++;
//     }
//     else
//     {
//         while (value[*i] && (ft_isalnum(value[*i]) || value[*i] == '_'))
//             (*i)++;
//         var_name = ft_substr(value, start, *i - start, gc);
//     }
//     if (!var_name)
//         return (NULL);
//     if (ft_strcmp(var_name, "?") == 0)
//         var_value = ft_itoa(g_exit_status, gc);
//     else
//     {
//         var_value = get_env_value(var_name, env);
//         if (!var_value)
//             var_value = "";
//     }
//     new_res = ft_strjoin(res, var_value, gc);
//     return (new_res);
// }

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

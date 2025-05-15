/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:40:17 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/05/14 23:01:47 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t countwords(char *str)
{
	size_t count;
	int word;
	char quote;
	int i;

	count = 0;
	word = 0;
	quote = 0;
	i = 0;
	while(str[i])
	{
		if (!word && (str[i] == ' ' || str[i] == '\t'))
		{
			word = 1;
			count++;
		}
		if (word && (str[i] == '\"' || str[i] == '\''))
		{
			if (!quote)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
			i++;
		}
		else if (word && quote)
			i++;
		else if (word && (str[i] == ' ' || str[i] == '\t'))
		{
			word = 0;
			i++;
		}
		else
			i++;
	}
	return (count);
}

char *ft_fill_str(char *str, t_gc **gc)
{
	int i;
	int j;
	char *new_str;
	char quote;

	i = 0;
	j = 0;
	quote = 0;
	while(str[j] && (quote || str[j] != ' ' || str[j] != '\t'))
	{
		if (!quote && (str[j] == '\'' || str[j] == '\"'))
		{

			quote = str[j];
			j++;
			while (str[j] && str[j] != quote)
				j++;
			if (str[j] == quote)
				j++;
			quote = 0;
		}
		else
			j++;
	}
	new_str = (char *)ft_malloc(j + 1, gc);
	if (!new_str)
		return (NULL);
	while (i < j)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char **ft_split_quotes(char *s, t_gc **gc)
{
	char **str;
	size_t len;
	size_t i;
	size_t j;

	if (!s)
		return (NULL);
	len = countwords(s) + 1;
	str = (char **)ft_malloc((sizeof(char *) * len), gc);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		while ((s[j] == ' ' || s[j] == '\t') && s[j])
			j++;
		str[i] = ft_fill_str(&s[j], gc);
		if (!str[i])
			return (NULL);
		while (s[j] && s[j] != ' ' && s[j] != '\t')
			j++;
		i++;
	}
	str[i] = NULL;
	return (str);
}

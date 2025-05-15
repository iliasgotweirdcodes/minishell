/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:40:17 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/05/15 19:07:07 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	countwords(char *str)
{
	size_t	count;
	int		i;
	char	quote;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			i++;
		if (!str[i])
			break;
		count++;
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == quote)
				i++;
		}
		else
		{
			while (str[i] && !is_space(str[i]) && str[i] != '\'' && str[i] != '\"')
				i++;
		}
	}
	return (count);
}

int	word_length(char *str)
{
	int		len;
	char	quote;

	len = 0;
	if (str[len] == '\'' || str[len] == '\"')
	{
		quote = str[len++];
		while (str[len] && str[len] != quote)
			len++;
		if (str[len] == quote)
			len++;
		return (len);
	}
	while (str[len] && !is_space(str[len]) && str[len] != '\'' && str[len] != '\"')
		len++;
	return (len);
}

char	*ft_fill_str(char *str, t_gc **gc)
{
	int		i;
	int		j;
	char	*new_str;
	int		len;

	i = 0;
	j = 0;
	len = word_length(str);
	new_str = (char *)ft_malloc(len + 1, gc);
	if (!new_str)
		return (NULL);
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	**ft_split_quotes(char *s, t_gc **gc)
{
	char	**str;
	size_t	len;
	size_t	i;
	size_t	j;
	int		wlen;

	if (!s)
		return (NULL);
	len = countwords(s);
	str = (char **)ft_malloc(sizeof(char *) * (len + 1), gc);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		while (is_space(s[j]) && s[j])
			j++;
		wlen = word_length(&s[j]);
		str[i] = ft_fill_str(&s[j], gc);
		if (!str[i])
			return (NULL);
		j += wlen;
		i++;
	}
	str[i] = NULL;
	return (str);
}

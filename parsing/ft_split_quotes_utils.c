/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:17:08 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/05/17 17:59:06 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_spaces(char *s, int i)
{
	while (s[i] && is_space(s[i]))
		i++;
	return (i);
}

int	word_len(char *s)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	if (!s[i])
		return (0);
	while (s[i] && !is_space(s[i]))
	{
		if (is_quote(s[i]))
		{
			quote = s[i++];
			j = i;
			while (s[j] && s[j] != quote)
				j++;
			if (s[j] == quote)
				j++;
			i = j;
		}
		else
			i++;
	}
	return (i);
}

int	count_words(char *s)
{
	int		i;
	int		count;
	int		len;

	i = 0;
	count = 0;
	while (s[i])
	{
		i = skip_spaces(s, i);
		if (!s[i])
			break;
		len = word_len(&s[i]);
		if (len > 0)
			count++;
		i += len;
	}
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:40:17 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/05/17 17:19:56 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_fill_str(char *s, char *word, int start, int len)
{
	int		pos;
	int		j;
	char	quote;

	pos = 0;
	j = 0;
	while (pos < len)
	{
		if (is_quote(s[start + pos]))
		{
			quote = s[start + pos];
			pos++;
			while (pos < len && s[start + pos] && s[start + pos] != quote)
				word[j++] = s[start + pos++];
			if (s[start + pos] == quote)
				pos++;
		}
		else
			word[j++] = s[start + pos++];
	}
	word[j] = '\0';
	return (j);
}

char	*get_next_word(char *s, int *i, t_gc **gc)
{
	int		start;
	int		len;
	char	*word;

	start = skip_spaces(s, *i);
	len = word_len(&s[start]);
	if (len == 0)
	{
		*i = start;
		return (NULL);
	}
	word = (char *)ft_malloc(len + 1, gc);
	if (!word)
		return (NULL);
	ft_fill_str(s, word, start, len);
	*i = start + len;
	if (word[0])
		return (word);
	return (NULL);
}

char	**ft_split_quotes(char *s, t_gc **gc)
{
	int		len;
	int		i;
	int		pos;
	char	**str;
	char	*word;

	if (!s)
		return (NULL);
	len = count_words(s);
	str = (char **)ft_malloc(sizeof(char *) * (len + 1), gc);
	if (!str)
		return (NULL);
	i = 0;
	pos = 0;
	while (i < len)
	{
		word = NULL;
		while (!word && s[pos])
			word = get_next_word(s, &pos, gc);
		if (!word)
			break;
		str[i++] = word;
	}
	str[i] = NULL;
	return (str);
}

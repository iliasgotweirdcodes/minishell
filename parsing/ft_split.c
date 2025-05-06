/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:37:53 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/05/02 17:13:43 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_countwords(char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

char	**ft_free(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (i >= 0)
		{
			free(str[i]);
			i--;
		}
		free(str);
	}
	return (NULL);
}

char	**ft_allocation(char **str, char *s, char c, t_gc **gc)
{
	size_t	i;
	size_t	j;
	size_t	start;
	size_t	end;

	i = 0;
	start = 0;
	while (i < ft_countwords(s, c))
	{
		while (s[start] == c && s[start])
			start++;
		end = start;
		while (s[end] != c && s[end])
			end++;
		str[i] = (char *)ft_malloc(end - start + 1, gc);
		if (!str[i])
			return (ft_free(str), NULL);
		j = 0;
		while (start < end)
			str[i][j++] = s[start++];
		str[i][j] = '\0';
		i++;
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split(char *s, char c , t_gc **gc)
{
	char		**str;
	size_t		len;

	if (!s)
		return (NULL);
	len = ft_countwords(s, c) + 1;
	str = (char **)ft_malloc(sizeof(char *) * len, gc);
	if (!str)
		return (NULL);
	str = ft_allocation(str, s, c , gc);
	if (!str)
		return (ft_free(str), NULL);
	return (str);
}

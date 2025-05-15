/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitvtab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:48:20 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/05/15 18:48:23 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_countwords_vtab(char *s)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == 32 || s[i] == '\t'))
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != 32 && s[i] != '\t')
			i++;
	}
	return (count);
}

char	**ft_allocation_vtab(char **str, char *s, t_gc **gc)
{
	size_t	i;
	size_t	j;
	size_t	start;
	size_t	end;

	i = 0;
	start = 0;
	while (i < ft_countwords_vtab(s))
	{
		while ((s[start] == ' ' || s[start] == '\t') && s[start])
			start++;
		end = start;
		while (s[end] != ' ' && s[end] != '\t' && s[end])
			end++;
		str[i] = (char *)ft_malloc(end - start + 1, gc);
		if (!str[i])
			return ( NULL);
		j = 0;
		while (start < end)
			str[i][j++] = s[start++];
		str[i][j] = '\0';
		i++;
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split_vtab(char *s, t_gc **gc)
{
	char		**str;
	size_t		len;

	if (!s)
		return (NULL);
	len = ft_countwords_vtab(s) + 1;
	str = (char **)ft_malloc((8 * len), gc);
	if (!str)
		return (NULL);
	str = ft_allocation_vtab(str, s, gc);
	if (!str)
		return (NULL);
	return (str);
}

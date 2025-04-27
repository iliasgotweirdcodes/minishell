/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:24:09 by aromani           #+#    #+#             */
/*   Updated: 2025/04/27 15:28:58 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../minishell.h"

char	*ft_substr(char *s, int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*sub;

	i = (size_t)start;
	j = 0;
	if (!s)
		return (NULL);
	if (!len || (i >= ft_strlen(s)))
		return (ft_strdup(""));
	if (len > ft_strlen(start + s))
		sub = malloc(ft_strlen(start + s) + 1);
	else
		sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	while (s[i] && j < len)
		sub[j++] = s[i++];
	sub[j] = '\0';
	return (sub);
}

int	ft_search(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*s;

	i = 0;
	if (!str)
		return (NULL);
	s = malloc(ft_strlen(str) + 1);
	while (str[i])
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}


int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*st1;
	unsigned char	*st2;

	i = 0;
	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	while (st1[i] || st2[i])
	{
		if (st1[i] != st2[i])
			return (st1[i] - st2[i]);
		i++;
	}
	return (0);
}

void ft_putstr(char *str)
{
    int i;

    i = 0;
    while (str[i])
        write (1, &str[i++], 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:26:34 by aromani           #+#    #+#             */
/*   Updated: 2025/04/29 16:00:45 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_substrv3(char *s, unsigned int start, size_t len, t_gc **exec)
{
	size_t	i;
	char	*str;
	size_t	s1len;

	if (!s)
		return (NULL);
	s1len = ft_strlen(s);
	if (start > s1len || len == 0)
		return (ft_strdup2("", exec));
	if (len > s1len - start)
		len = s1len - start;
	str = ft_malloc(len + 1, exec);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[len] = '\0';
	return (str);
}

int	ft_search2(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strjoinv2(char *s1, char *s2, t_gc **exec)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 2, exec);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '/';
	i++;
	while (s2[j])
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
static char	*pathchecker(char *c, char *paths, t_gc **exec)
{
	char	**pth;
	char	*tmp2;
	size_t	i;

	i = 0;
	pth = ft_split(paths, ':');
	if (!pth)
		return (NULL);
	while (pth[i])
	{
		if (ft_search2(c, '/') != -1)
			tmp2 = ft_strdup(c);
		else
			tmp2 = ft_strjoinv2(pth[i], c, exec);
		if (access(tmp2, X_OK) != -1)
		{
			return (tmp2);
		}
		i++;
	}
	return (NULL);
}

static char	*access_path(char *cmd, char *path, t_gc **exec)
{
	char	*p;

	p = pathchecker(cmd, path, exec);
	if (!p)
		return (NULL);
	else
		return (p);
}

char	*path_geter(char *str, char **ev)
{
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	while (ev[i])
	{
		while (ev[i][j] == str[j])
		{
			j++;
			if (ev[i][j] == str[j])
				j++;
		}
		if (j == ft_strlen(str))
			return (ev[i]);
		i++;
	}
	return (NULL);
}

char	*last_path(char **env, char **arg, t_gc **exec)
{
	char	*path;
	char	*str;
	char	*tmp;

	path = path_geter("PATH", env);
	if (!path)
		return (NULL);
	str = ft_substrv3(path, (ft_search2(path, '=') + 1), ft_strlen(path), exec);
	tmp = access_path(arg[0], str, exec);
	if (!tmp)
		return (NULL);
	return (tmp);
}

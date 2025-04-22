/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envirement.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:26:34 by aromani           #+#    #+#             */
/*   Updated: 2025/04/22 15:03:36 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*access_path(char *cmd, char *path)
{
	char	*p;

	p = pathchecker(cmd, path);
	if (!p)
		return (free(p), NULL);
	else
		return (p);
}

static char	*path_geter(char *str, char **ev)
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

static char	*pathchecker(char *c, char *paths)
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
		if (ft_searchh(c, '/') != -1)
			tmp2 = ft_strdup(c);
		else
			tmp2 = ft_strjoin(pth[i], c);
		if (access(tmp2, X_OK) != -1)
		{
			ft_free (pth, count_words(paths, ':'));
			return (tmp2);
		}
		else
			free (tmp2);
		i++;
	}
	return (ft_free(pth, count_words(paths, ':')), NULL);
}

char	*last_path(char **env, char **arg)
{
	char	*path;
	char	*str;
	char	*tmp;

	path = path_geter("PATH", env);
	if (!path)
		return (NULL);
	str = ft_substr(path, (ft_search(path, '=') + 1), ft_strlen(path));
	tmp = access_path(arg[0], str);
	free (str);
	if (!tmp)
		return (NULL);
	return (tmp);
}

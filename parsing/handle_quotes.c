/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:48:32 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/05/17 15:44:21 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_remove_quotes(char *str, t_gc **gc)
{
	int		len;
	int		i;
	int		j;
	char	*new_str;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	new_str = (char *)ft_malloc(len + 1, gc);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void	remove_quotes(char **str, t_gc **gc)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str && str[i])
	{
		tmp = ft_remove_quotes(str[i], gc);
		str[i] = tmp;
		i++;
	}
}

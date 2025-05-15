/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:48:32 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/05/15 21:25:57 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_lquotes(const char *str, char quote)
{
	int	count;

	count = 0;
	while (str[count] && str[count] == quote)
		count++;
	return (count);
}

int	count_rquotes(const char *str, int len, char quote)
{
	int	count;

	count = 0;
	while (len - 1 - count >= 0 && str[len - 1 - count] == quote)
		count++;
	return (count);
}

char	*ft_remove_quotes(char *str, t_gc **gc)
{
	int		len;
	char	quote;
	int		left;
	int		right;
	char	*new_str;
	int		i;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len < 2)
		return (ft_strdup(str, gc));
	while (len > 1 && (str[0] == '\'' || str[0] == '\"'))
	{
		quote = str[0];
		left = count_lquotes(str, quote);
		right = count_rquotes(str, len, quote);
		if (left == right && left > 0 && len > 2 * left - 1)
		{
			str = str + left;
			len = len - 2 * left;
		}
		else
			break;
	}
	new_str = (char *)ft_malloc(len + 1, gc);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
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

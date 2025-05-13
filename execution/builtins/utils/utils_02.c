/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:32:33 by aromani           #+#    #+#             */
/*   Updated: 2025/05/13 16:39:33 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

// int	ft_isalnum(int c)
// {
// 	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
// 		|| (c >= 'A' && c <= 'Z'))
// 		return (1);
// 	return (0);
// }

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_revsrch(const char *s, int c)
{
	int		i;
	char	*p;

	i = 0;
	p = (char *)s;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (p[i] == (char)c)
			return (i);
		i--;
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
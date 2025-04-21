/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:31:16 by ilel-hla          #+#    #+#             */
/*   Updated: 2024/11/09 11:54:06 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*h;
	char	*n;

	h = (char *)haystack;
	n = (char *)needle;
	i = 0;
	j = 0;
	if (needle[0] == '\0')
		return (h);
	while (i < len && h[i])
	{
		while (h[i + j] == n[j] && n[j] && i + j < len)
		{
			j++;
		}
		if (n[j] == '\0')
			return (h + i);
		j = 0;
		i++;
	}
	return (NULL);
}

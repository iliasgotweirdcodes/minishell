/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 23:12:58 by ilel-hla          #+#    #+#             */
/*   Updated: 2024/10/24 21:40:21 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	char	*str;

	str = (char *)s;
	c = (char)c;
	len = ft_strlen(s);
	while (len > 0)
	{
		if (str[len] == (char)c)
		{
			return (str + len);
		}
		len--;
	}
	if (str[len] == c)
		return (str);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:22:32 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/05/07 18:35:20 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_nb(int nb)
{
	int		count;

	count = 0;
	if (nb <= 0)
	{
		count++;
	}
	while (nb != 0)
	{
		count++;
		nb /= 10;
	}
	return (count);
}

char	*ft_itoa(int n, t_gc **gc)
{
	int		len;
	char	*str;

	len = len_nb(n);
	str = ft_malloc(len + 1, gc);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		if (n == -2147483648)
		{
			str[--len] = '8';
			n /= 10;
		}
		n = -n;
	}
	while (len-- && n != 0)
	{
		str[len] = (n % 10) + 48;
		n /= 10;
	}
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:20:27 by aromani           #+#    #+#             */
/*   Updated: 2025/05/06 18:21:23 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	signcheck(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

static	int	counter(long n)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (n < 0)
		n *= -1;
	if (n > 9)
	{
		while (n > 9)
		{
			n /= 10;
			count++;
		}
	}
	if (n <= 9)
		count++;
	return (count);
}

static void	maincode(char *ptr, int len, long n, int sig)
{
	if (n < 0)
		n *= -1;
	while (len >= 0)
	{
		ptr[len] = (n % 10) + 48;
		n /= 10;
		len--;
	}
	if (sig == 1)
		ptr[0] = '-';
}

char	*ft_itoa(int nbr)
{
	int		sig;
	int		count;
	int		len;
	long	n;
	char	*ptr;

	n = (long)nbr;
	sig = signcheck(n);
	count = counter(n);
	len = count + sig;
	ptr = (char *)malloc(len + 1);
	if (!ptr)
		return (NULL);
	len--;
	maincode(ptr, len, n, sig);
	ptr[count + sig] = '\0';
	return (ptr);
}
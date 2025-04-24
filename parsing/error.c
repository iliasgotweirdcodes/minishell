/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 23:17:04 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/04/24 21:40:43 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
}

void	print_quote_error(void)
{
	write(2, "minishell: syntax error: unclosed quote\n", 40);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:25:14 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/04/25 17:57:36 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*ft_lstnew(char **content)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->cmd = content;
	node->in_out = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);

	// there is lot to change in this t_token  ft_lstnew(t_tokens *token);
}

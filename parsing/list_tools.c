/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:25:14 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/04/30 23:43:20 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*ft_lstnew(char **content, t_gc **gc)
{
	t_command	*node;

	node = ft_malloc(sizeof(t_command), gc);
	if (!node)
		return (NULL);
	node->cmd = content;
	node->in_out = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);

	// there is lot to change in this t_token  ft_lstnew(t_tokens *token);
}

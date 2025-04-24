/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:25:14 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/04/24 18:33:29 by ilel-hla         ###   ########.fr       */
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
	node->next = NULL;
	return (node);
}

// void	ft_lstadd_back(t_command **lst, t_command *new)
// {
// 	t_command	*node;

// 	if (!*lst)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	node = ft_lstlast(*lst);
// 	node->next = new;
// 	new->next = NULL;
// }

// t_command	*ft_lstlast(t_command *lst)
// {
// 	if (!lst)
// 		return (NULL);
// 	while (lst->next)
// 		lst = lst->next;
// 	return (lst);
// }

// void	ft_lstclear(t_command **lst, void (*del)(void*))
// {
// 	t_command	*tmp;

// 	if (!lst || !del)
// 		return ;
// 	tmp = *lst;
// 	while (*lst)
// 	{
// 		tmp = tmp->next;
// 		del((*lst)->content);
// 		free(*lst);
// 		*lst = tmp;
// 	}
// 	*lst = NULL;
// }

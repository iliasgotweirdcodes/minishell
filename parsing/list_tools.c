/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:25:14 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/05/06 16:24:35 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*create_token_copy(t_token *src, t_gc **gc)
{
	t_token	*copy;

	copy = ft_malloc(sizeof(t_token), gc);
	if (!copy)
		return (NULL);
	copy->type = src->type;
	copy->value = ft_strdup(src->value, gc);
	copy->next = NULL;
	return (copy);
}

t_token	*split_cmd_tokens(t_token *start, t_token *end, t_gc **gc)
{
	t_token	*head;
	t_token	**tail;
	t_token	*current;

	head = NULL;
	tail = &head;
	current = start;
	while (current && current != end)
	{
		*tail = create_token_copy(current, gc);
		if (!*tail)
			return (NULL);
		tail = &(*tail)->next;
		current = current->next;
	}
	return (head);
}


t_command	*create_cmd_node(t_token *tokens, t_gc **gc)
{
	t_command	*node;

	node = ft_malloc(sizeof(t_command), gc);
	if (!node)
		return (NULL);
	node->cmd = prepare_cmd(tokens, gc);
	node->in_out = prepare_in_out(tokens, gc);
	node->next = NULL;
	node->prev = NULL;
	node->here_docfd = 0;
	return (node);
}

void	cmd_list_add_back(t_command **lst, t_command *new_node)
{
	t_command	*last;

	if (!*lst)
		*lst = new_node;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new_node;
		new_node->prev = last;
	}
}

void	create_cmd_list(t_token *tokens, t_command **cmds, t_gc **gc)
{
	t_token		*cmd_start;
	t_token		*cmd_end;

	cmd_start = tokens;
	while (cmd_start)
	{
		cmd_end = cmd_start;
		while (cmd_end && cmd_end->type != PIPE)
			cmd_end = cmd_end->next;
		cmd_list_add_back(cmds, create_cmd_node(
				split_cmd_tokens(cmd_start, cmd_end, gc), gc));
		if (cmd_end && cmd_end->type == PIPE)
			cmd_start = cmd_end->next;
		else
			cmd_start = NULL;
	}
}

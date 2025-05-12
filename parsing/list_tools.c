/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:25:14 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/05/12 17:21:51 by aromani          ###   ########.fr       */
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
	copy->here_docfd = src->here_docfd;
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

// int prepare_fd(t_token *token, t_command *cmd)
// {
// 	t_token *tmp1;
// 	t_token *tmp2;

// 	tmp1 = token;
// 	tmp2 = NULL;
// 	while (token)
// 	{
// 		if (token->type == HEREDOC)
// 			tmp2 = token;
// 		token = token->next;
// 	}
// 	// if (!tmp2)
// 	// 	tmp2->here_docfd = -1;
// 	// else
// 	// {
// 	cmd->here_docfd = tmp2->here_docfd;
// 	while (tmp1 && tmp1 != tmp2)
// 	{
// 		if (tmp1->type == HEREDOC)
// 			close(tmp1->here_docfd);
// 		tmp1=tmp1->next;
// 	}
// 	// }
// 	return (tmp2->here_docfd);
// }

t_command	*create_cmd_node(t_token *tokens, t_gc **gc)
{
	t_command	*node;
	t_token *temp = tokens;
    t_token *here = NULL;

	node = ft_malloc(sizeof(t_command), gc);
	if (!node)
		return (NULL);
	node->cmd = prepare_cmd(tokens, gc);
	node->in_out = prepare_in_out(tokens, gc);
	node->next = NULL;
	node->prev = NULL;
    while(tokens)
    {
        if (tokens->type == HEREDOC)
            here = tokens;
        tokens = tokens->next;
    }
    if (!here)
        node->here_docfd = -1;
    else {
        node->here_docfd = here->here_docfd;
        while(temp && temp != here)
        {
            if (temp->type == HEREDOC)
                close(temp->here_docfd);
            temp = temp->next;
        }
    }
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

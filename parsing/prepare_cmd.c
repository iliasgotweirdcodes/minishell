/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:54:52 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/05/01 15:54:54 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_pipe(t_token *tokens)
{
	if (tokens->type == PIPE)
		return (1);
	return (0);
}

size_t	count_cmd(t_token **tokens)
{
	t_token	*current;
	size_t		cmd_count;

	cmd_count = 0;
	current = *tokens;
	while (current)
	{
		if (current->type == WORD)
		{
			if (!current->prev || !is_redirection(current->prev->type))
				cmd_count++;
		}
		current = current->next;
	}
	return (cmd_count);
}

char	*get_cmdline(t_token *tokens, t_gc **gc)
{
	char	*cmd_line;
	char	*temp;
	t_token	*current;

	cmd_line = NULL;
	current = tokens;
	while (current)
	{
		if (current->type == WORD && (!current->prev || !is_redirection(current->prev->type)))
		{
			temp = ft_strjoin(cmd_line, " ", gc);
			free(cmd_line);
			cmd_line = ft_strjoin(temp, current->value, gc);
			free(temp);
			if (!cmd_line)
				return (NULL);
		}
		current = current->next;
	}
	return (cmd_line);
}

void	prepare_cmd(t_command **cmd, t_token *tokens, t_gc **gc)
{
	char	**tmp;
	char	*cmd_line;

	cmd_line = get_cmdline(tokens, gc);
	if (!cmd_line || !*cmd_line)
	{
		free(cmd_line);
		return ;
	}
	tmp = ft_split(cmd_line, ' ', gc);
	if (!tmp)
	{
		free(cmd_line);
		return ;
	}
	*cmd = ft_lstnew(tmp, gc);
	printf("cmd_line = %s\n", cmd_line);
	free(cmd_line);
}

// void prepare_in_out(t_command **in_out, t_token *tokens, t_gc **gc)
// {
//     t_token *current = tokens;
//     t_command **current_ptr = in_out; // Pointer to track insertion point

//     *in_out = NULL; // Initialize the list head

//     while (current)
//     {
//         if (current->type == REDIR_IN || current->type == REDIR_OUT ||
//             current->type == APPEND || current->type == HEREDOC)
//         {
//             // Ensure there's a filename token after the redirection operator
//             if (!current->next)
//             {
//                 // Handle error: missing filename for redirection
//                 fprintf(stderr, "minishell: syntax error near unexpected token\n");
//                 return;
//             }

//             // Create a new node with the FILENAME (next token's value)
//             t_command *new_node = ft_lstnew(&current->next->value, gc);
//             if (!new_node)
//                 return; // Handle allocation failure

//             // Link the new node into the list
//             *current_ptr = new_node;
//             current_ptr = &new_node->next;

//             // Set the redirection type if needed (adjust based on your struct)
//             new_node->in_out = current->type;

//             // Skip over the redirection operator and filename tokens
//             current = current->next->next;
//         }
//         else
//         {
//             // Move to next token if not a redirection
//             current = current->next;
//         }
//     }
// }

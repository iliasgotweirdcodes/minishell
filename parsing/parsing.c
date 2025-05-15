/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:17:39 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/05/14 23:20:53 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*parse_cmd(char *input, t_env *m_env, t_gc **gc)
{
	t_token	*tokens;

	tokens = ft_tokenization(input, gc);
	if (!tokens)
	{
		if (ft_strchr(input, '\'') || ft_strchr(input, '\"'))
			ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		return (NULL);
	}
	if (validate_syntax(tokens))
	{
		ft_gcfree(gc);
		return (NULL);
	}
	expand_tokens(&tokens, m_env, gc);
	return (tokens);
}

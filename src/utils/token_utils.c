/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:11:40 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/24 14:12:13 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*new_token(char *value, enum e_token_type type, t_minishell *mini)
{
	t_token	*new;

	if (*value == '\0' || !value)
	{
		safe_exit(mini);
		return (NULL);
	}
	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new)
		safe_exit(mini);
	new->value = value;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	token_lstadd_back(t_token **tokens, t_token *new)
{
	t_token	*curr;

	if (!tokens || !new)
		return ;
	if (!*tokens)
		*tokens = new;
	else
	{
		curr = *tokens;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

void	free_token_list(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}

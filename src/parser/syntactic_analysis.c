/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntactic_analysis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:27:08 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/29 09:33:24 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	syntactic_analysis(t_minishell *mini)
{
	t_process	*p;
	t_token		*token;
	int			count;

	p = mini->process_list;
	while (p)
	{
		token = p->tokens;
		count = 0;
		while (token)
		{
			if (count++ == 0)
			{
				if (token->type == CMD || token->type == BUILTIN)
					p->found_cmd = true;
			}
			token = token->next;
		}
		p = p->next;
	}
	return (true);
}

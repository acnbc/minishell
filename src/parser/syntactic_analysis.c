/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntactic_analysis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:27:08 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/04 09:21:52 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	has_redirection_without_target(t_process *p)
{
	if (p->redirect_in_flag && !p->input_file)
		return (true);
	if (p->heredoc_flag && !p->delimiter)
		return (true);
	if ((p->redirect_out_flag || p->append_flag) && !p->output_file)
		return (true);
	return (false);
}

static bool	syntax_error_msg(const char *msg)
{
	write(2, "Syntax error: ", 14);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (false);
}

bool	syntactic_analysis(t_minishell *mini)
{
	t_process	*p;
	
	p = mini->process_list;
	while (p)
	{
		if (has_redirection_without_target(p))
			return (syntax_error_msg("Missing redirection target"));
		p = p->next;
	}
	return (true);
}
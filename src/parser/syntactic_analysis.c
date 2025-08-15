/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntactic_analysis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:27:08 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/14 21:29:20 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	has_redirection_without_target(t_process *p)
{
	if (p->redirect_in_flag && !p->input_file)
		return (true);
	if (p->heredoc_flag && !p->heredoc_delimiter)
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

bool	syntactic_analysis(t_minishell *minishell)
{
	t_process	*p;
	t_token		*token;

	p = minishell->process_list;
	while (p)
	{
		p->found_cmd = false;
		token = p->tokens;
		if (has_redirection_without_target(p))
			return (syntax_error_msg("Missing redirection target"));
		while (token)
		{
			if ((token->type == CMD || token->type == BUILTIN) && p->found_cmd)
				return (syntax_error_msg("Multiple commands without pipe"));
			if (token->type == CMD || token->type == BUILTIN)
				p->found_cmd = true;
			if (!p->found_cmd && token->type == ARGS && token != p->tokens)
				return (syntax_error_msg("Unexpected argument before command"));
			token = token->next;
		}
		if (!p->found_cmd)
			return (syntax_error_msg("Missing command"));
		p = p->next;
	}
	return (true);
}

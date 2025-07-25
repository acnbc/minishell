/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntatic_analysis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:27:08 by anogueir          #+#    #+#             */
/*   Updated: 2025/07/19 19:27:10 by anogueir         ###   ########.fr       */
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

static bool	syntax_error(const char *msg)
{
	printf("Syntax error: %s\n", msg);
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
			return (syntax_error("Missing redirection target"));
		while (token)
		{
			if ((token->type == CMD || token->type == BUILTIN) && p->found_cmd)
				return (syntax_error("Multiple commands without pipe"));
			if (token->type == CMD || token->type == BUILTIN)
				p->found_cmd = true;
			if (!p->found_cmd && token->type == ARGS)
				return (syntax_error("Argument before command"));
			token = token->next;
		}
		if (!p->found_cmd)
			return (syntax_error("Missing command"));
		p = p->next;
	}
	return (true);
}

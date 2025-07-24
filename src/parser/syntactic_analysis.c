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
		return true;
	if (p->heredoc_flag && !p->heredoc_delimiter)
		return true;
	if ((p->redirect_out_flag || p->append_flag) && !p->output_file)
		return true;
	return false;
}

static bool	syntax_error(const char *msg)
{
	printf("Syntax error: %s\n", msg);
	return false;
}

bool	syntactic_analysis(t_minishell *minishell)
{
	t_process	*process;
	t_token		*token;
	bool		found_cmd;

	process = minishell->process_list;
	while (process)
	{
		found_cmd = false;
		token = process->tokens;

		if (has_redirection_without_target(process))
			return syntax_error("Missing redirection target");
		while (token)
		{
			if ((token->type == TOKEN_CMD || token->type == TOKEN_BUILTIN) && found_cmd)
				return syntax_error("Multiple commands without pipe");
		
			if (token->type == TOKEN_CMD || token->type == TOKEN_BUILTIN)
				found_cmd = true;
		
			if (!found_cmd && token->type == TOKEN_ARGS)
				return syntax_error("Argument before command");
		
			token = token->next;
		}
		if (!found_cmd)
			return syntax_error("Missing command");
		process = process->next;
	}
	return true;
}


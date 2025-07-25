/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:11:57 by anogueir          #+#    #+#             */
/*   Updated: 2025/07/19 19:11:59 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_redirection_token(t_minishell *minishell, int *i, int start)
{
	get_word_token(minishell, i, start);
}

static void	handle_whitespace_token(t_minishell *minishell, int *i, int *start)
{
	if (*i > *start)
		get_word_token(minishell, i, *start);
	skip_spaces(minishell->current_process->cmd_seq, i);
	*start = *i;
}

static void	handle_quote_token(t_minishell *minishell, int *i, int *start)
{
	t_token	**tokens;
	char	*cmd_seq;

	tokens = &minishell->current_process->tokens;
	cmd_seq = minishell->current_process->cmd_seq;
	if (*i > *start)
		token_lstadd_back(tokens, new_token(is_variable(minishell, i, *start),
				ARGS, minishell));
	token_lstadd_back(tokens, new_token(handle_quotes(minishell, cmd_seq, i),
			ARGS, minishell));
	*start = *i;
}

void	word_tokenizer(t_minishell *minishell, int *i)
{
	char	*cmd_seq;
	int		start;

	cmd_seq = minishell->current_process->cmd_seq;
	start = *i;
	while (cmd_seq[*i])
	{
		if ((cmd_seq[*i] == '>' || cmd_seq[*i] == '<')
			&& !is_between_quotes(cmd_seq, *i))
			return (handle_redirection_token(minishell, i, start));
		else if (ft_isspace(cmd_seq[*i]))
			handle_whitespace_token(minishell, i, &start);
		else if (cmd_seq[*i] == DOUBLE_QUOTE || cmd_seq[*i] == SINGLE_QUOTE)
			handle_quote_token(minishell, i, &start);
		else
			(*i)++;
	}
	if (*i > start)
		get_word_token(minishell, i, start);
}

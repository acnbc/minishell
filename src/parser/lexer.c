/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:23:12 by anogueir          #+#    #+#             */
/*   Updated: 2025/07/19 16:23:14 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redout_append_tokenizer(t_process *process, t_minishell *minishell,
		int *i)
{
	if (process->cmd_seq[*i + 1] && process->cmd_seq[*i + 1] == '>')
	{
		*i += 2;
		process->append_flag = 1;
	}
	else
	{
		*i += 1;
		process->redirect_out_flag = 1;
	}
	skip_spaces(process->cmd_seq, i);
	if (process->cmd_seq[*i] == DOUBLE_QUOTE
		|| process->cmd_seq[*i] == SINGLE_QUOTE)
		process->output_file = handle_quotes(minishell, process->cmd_seq, i);
	else
		process->output_file = get_str(process->cmd_seq, i, minishell);
	skip_spaces(process->cmd_seq, i);
	return ;
}

void	redin_heredoc_tokenizer(t_process *process, t_minishell *minishell,
		int *i)
{
	char    *temp;
    
    if (process->cmd_seq[*i + 1] && process->cmd_seq[*i + 1] == '<')
	{
		*i += 2;
		process->heredoc_flag = 1;
	}
	else
    {
        *i += 1;
	    process->redirect_in_flag = 1;
    }
	skip_spaces(process->cmd_seq, i);
	if (process->cmd_seq[*i] == DOUBLE_QUOTE
		|| process->cmd_seq[*i] == SINGLE_QUOTE)
		temp = handle_quotes(minishell, process->cmd_seq, i);
	else
		temp = get_str(process->cmd_seq, i, minishell);
	skip_spaces(process->cmd_seq, i);
    if (process->heredoc_flag)
        process->heredoc_delimiter = temp;
    else
        process->input_file = temp;
    return ;
}

void	word_tokenizer(t_token **tokens, t_process *process,
		t_minishell *minishell, int *i)
{
	char	*segment;
	int		start;

	minishell->current_process = process->cmd_seq;
	start = *i;
	while (minishell->current_process[*i])
	{
		if ((minishell->current_process[*i] == '>'
				|| minishell->current_process[*i] == '<')
			&& !is_between_quotes(minishell->current_process, *i))
		{
			get_word_token(tokens, minishell, i, start);
			return ;
		}
		else if (ft_isspace(minishell->current_process[*i]))
		{
			if (*i > start)
				get_word_token(tokens, minishell, i, start);
			skip_spaces(minishell->current_process, i);
			start = *i;
			continue ;
		}
		else if (minishell->current_process[*i] == DOUBLE_QUOTE
			|| minishell->current_process[*i] == SINGLE_QUOTE)
		{
			if (*i > start)
			{
				segment = is_variable(minishell->current_process, minishell, i,
						start);
				token_lstadd_back(tokens, new_token(segment, TOKEN_ARGS));
			}
			token_lstadd_back(tokens, new_token(handle_quotes(minishell,
						minishell->current_process, i), TOKEN_ARGS));
			start = *i;
		}
		else
			(*i)++;
	}
	if (*i > start)
		get_word_token(tokens, minishell, i, start);
	return ;
}

void	lexer(t_minishell *minishell)
{
	t_process	*current_process;
	char		*cmd_seq;

	current_process = minishell->process_list;
	while (current_process)
	{
		cmd_seq = current_process->cmd_seq;
		tokenize(cmd_seq, current_process, minishell);
		current_process = current_process->next;
	}
	return ;
}

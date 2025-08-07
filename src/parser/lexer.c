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

static char	*get_redir_target(t_minishell *minishell, int *i)
{
	char	*cmd_seq;
	char	*temp;

	cmd_seq = minishell->current_process->cmd_seq;
	skip_spaces(cmd_seq, i);
	if (cmd_seq[*i] == DOUBLE_QUOTE || cmd_seq[*i] == SINGLE_QUOTE)
	{
		temp = handle_quotes(minishell, cmd_seq, i);
		minishell->current_process->heredoc_quote_flag = 1;
	}
	else
		temp = get_str(cmd_seq, i, minishell);
	skip_spaces(cmd_seq, i);
	if (temp && (ft_strchr(temp, '<') || ft_strchr(temp, '>')))
	{
    	free(temp);
    	temp = NULL;
	}
	return (temp);
}

void	redout_append_tokenizer(t_minishell *minishell, int *i)
{
	char	*cmd_seq;

	cmd_seq = minishell->current_process->cmd_seq;
	if (cmd_seq[*i + 1] && cmd_seq[*i + 1] == '>')
	{
		*i += 2;
		minishell->current_process->append_flag = 1;
	}
	else
	{
		*i += 1;
		minishell->current_process->redirect_out_flag = 1;
	}
	if (minishell->current_process->output_file)
		free(minishell->current_process->output_file);
	minishell->current_process->output_file = get_redir_target(minishell, i);
	return ;
}

void	redin_heredoc_tokenizer(t_minishell *minishell, int *i)
{
	char	*temp;
	char	*cmd_seq;

	cmd_seq = minishell->current_process->cmd_seq;
	if (cmd_seq[*i + 1] && cmd_seq[*i + 1] == '<')
	{
		*i += 2;
		minishell->current_process->heredoc_flag = 1;
	}
	else
	{
		*i += 1;
		minishell->current_process->redirect_in_flag = 1;
	}
	temp = get_redir_target(minishell, i);
	if (minishell->current_process->heredoc_flag)
	{
		if (minishell->current_process->heredoc_delimiter)
			free(minishell->current_process->heredoc_delimiter);
		minishell->current_process->heredoc_delimiter = temp;
	}
	else
	{
		if (minishell->current_process->input_file)
			free(minishell->current_process->input_file);
		minishell->current_process->input_file = temp;
	}
	return ;
}

void	lexer(t_minishell *minishell)
{
	t_process	*current_process;

	current_process = minishell->process_list;
	while (current_process)
	{
		minishell->current_process = current_process;
		tokenize(minishell);
		current_process = current_process->next;
	}
	return ;
}

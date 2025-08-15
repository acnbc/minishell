/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:23:12 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/15 09:10:10 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_redir_target(t_minishell *mini, int *i)
{
	char	*cmd_seq;
	char	*temp;

	cmd_seq = mini->current_process->cmd_seq;
	skip_spaces(cmd_seq, i);
	if (cmd_seq[*i] == DOUBLE_QUOTE || cmd_seq[*i] == SINGLE_QUOTE)
	{
		temp = handle_quotes(mini, cmd_seq, i);
		mini->current_process->heredoc_quote_flag = 1;
	}
	else
		temp = get_str(cmd_seq, i, mini);
	skip_spaces(cmd_seq, i);
	if (temp && (ft_strchr(temp, '<') || ft_strchr(temp, '>')))
	{
		free(temp);
		temp = NULL;
	}
	return (temp);
}

static void	assign_file(char **file, t_minishell *mini, int *i)
{
	if (*file)
		free(*file);
	*file = get_redir_target(mini, i);
}

void	redout_append_tokenizer(t_minishell *mini, int *i)
{
	char	*cmd_seq;

	cmd_seq = mini->current_process->cmd_seq;
	if (cmd_seq[*i + 1] && cmd_seq[*i + 1] == '>')
	{
		*i += 2;
		mini->current_process->append_flag = 1;
	}
	else
	{
		*i += 1;
		mini->current_process->redirect_out_flag = 1;
	}
	assign_file(&mini->current_process->output_file, mini, i);
	return ;
}

void	redin_heredoc_tokenizer(t_minishell *mini, int *i)
{
	char	*cmd_seq;

	cmd_seq = mini->current_process->cmd_seq;
	if (cmd_seq[*i + 1] && cmd_seq[*i + 1] == '<')
	{
		*i += 2;
		mini->current_process->heredoc_flag = 1;
	}
	else
	{
		*i += 1;
		mini->current_process->redirect_in_flag = 1;
	}
	if (mini->current_process->heredoc_flag)
		assign_file(&mini->current_process->delimiter, mini, i);
	else
		assign_file(&mini->current_process->input_file, mini, i);
	return ;
}

void	lexer(t_minishell *mini)
{
	t_process	*current_process;

	current_process = mini->process_list;
	while (current_process)
	{
		mini->current_process = current_process;
		tokenize(mini);
		current_process = current_process->next;
	}
	return ;
}

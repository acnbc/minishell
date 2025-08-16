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

	cmd_seq = mini->cur_proc->cmd_seq;
	skip_spaces(cmd_seq, i);
	if (cmd_seq[*i] == DOUBLE_QUOTE || cmd_seq[*i] == SINGLE_QUOTE)
	{
		temp = handle_quotes(mini, cmd_seq, i);
		mini->cur_proc->heredoc_quote_flag = 1;
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

	cmd_seq = mini->cur_proc->cmd_seq;
	// corrigir >>>
	if (cmd_seq[*i + 1] && cmd_seq[*i + 1] == '>')
	{
		*i += 2;
		mini->cur_proc->append_flag = 1;
	}
	else
	{
		*i += 1;
		mini->cur_proc->redirect_out_flag = 1;
	}
	assign_file(&mini->cur_proc->output_file, mini, i);
	return ;
}

void	redin_heredoc_tokenizer(t_minishell *mini, int *i)
{
	char	*cmd_seq;

	cmd_seq = mini->cur_proc->cmd_seq;
	// corrigir <<<
	if (cmd_seq[*i + 1] && cmd_seq[*i + 1] == '<')
	{
		*i += 2;
		mini->cur_proc->heredoc_flag = 1;
	}
	else
	{
		*i += 1;
		mini->cur_proc->redirect_in_flag = 1;
	}
	if (mini->cur_proc->heredoc_flag)
		assign_file(&mini->cur_proc->delimiter, mini, i);
	else
		assign_file(&mini->cur_proc->input_file, mini, i);
	return ;
}

void	lexer(t_minishell *mini)
{
	t_process	*cur_proc;

	cur_proc = mini->process_list;
	while (cur_proc)
	{
		mini->cur_proc = cur_proc;
		tokenize(mini);
		cur_proc = cur_proc->next;
	}
	return ;
}

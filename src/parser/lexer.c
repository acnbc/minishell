/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:23:12 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/30 20:53:34 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_redir_target(t_minishell *mini, int *i)
{
	char	*cmd_seq;
	char	*temp;

	cmd_seq = mini->cur_proc->cmd_seq;
	skip_spaces(cmd_seq, i);
	if (!is_stopchar(cmd_seq[*i]))
		return (NULL);
	if (cmd_seq[*i] == DOUBLE_QUOTE || cmd_seq[*i] == SINGLE_QUOTE)
	{
		temp = handle_quotes(mini, cmd_seq, i);
		mini->cur_proc->heredoc_quote_flag = 1;
	}
	else
		temp = get_str(cmd_seq, i, mini);
	skip_spaces(cmd_seq, i);
	if (temp && (ft_strchr(temp, '<') || ft_strchr(temp, '>')
			|| is_builtin(temp) || is_cmd(temp, mini)))
	{
		free(temp);
		temp = NULL;
	}
	return (temp);
}

int	assign_file(char **file, t_minishell *mini, int *i)
{
	if (*file)
		free(*file);
	*file = get_redir_target(mini, i);
	if (!*file)
	{
		write(2, "heredoc syntax error\n", 21);
		return (0);
	}
	return (1);
}

int	redout_append_tokenizer(t_minishell *mini, int *i)
{
	char	*cmd_seq;

	cmd_seq = mini->cur_proc->cmd_seq;
	if (cmd_seq[*i + 1] && cmd_seq[*i + 1] == '>'
		&& cmd_seq[*i + 2] && cmd_seq[*i + 2] == '>')
		return (0);
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
	if (!assign_file(&mini->cur_proc->output_file, mini, i))
		return (0);
	return (1);
}

int	redin_heredoc_tokenizer(t_minishell *mini, int *i)
{
	char	*cmd_seq;

	cmd_seq = mini->cur_proc->cmd_seq;
	if (cmd_seq[*i + 1] && cmd_seq[*i + 1] == '<'
		&& cmd_seq[*i + 2] && cmd_seq[*i + 2] == '<')
		return (0);
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
	return (handle_redirect_assignment(mini, i));
}

int	lexer(t_minishell *mini)
{
	t_process	*cur_proc;

	cur_proc = mini->process_list;
	while (cur_proc)
	{
		mini->cur_proc = cur_proc;
		if (!tokenize(mini))
			return (0);
		cur_proc = cur_proc->next;
	}
	return (1);
}

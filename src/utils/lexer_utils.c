/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:58:45 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/01 10:49:32 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_redirect_assignment(t_minishell *mini, int *i)
{
	if (mini->cur_proc->heredoc_flag)
	{
		if (!assign_file(&mini->cur_proc->delimiter, mini, i))
			return (0);
	}
	else
	{
		if (!assign_file(&mini->cur_proc->input_file, mini, i))
			return (0);
	}
	return (1);
}

void	get_word_token(t_minishell *mini, int *i, int start)
{
	t_token				**tokens;
	char				*segment;
	enum e_token_type	type;

	tokens = &mini->cur_proc->tokens;
	segment = is_variable(mini, i, start);
	if (!segment)
		return ;
	if (is_builtin(segment))
	{
		token_lstadd_back(tokens, new_token(segment, BUILTIN, mini));
		return ;
	}
	else if (!mini->cur_proc->path && is_cmd(segment, mini))
		type = CMD;
	else
		type = ARGS;
	token_lstadd_back(tokens, new_token(segment, type, mini));
}

char	*is_variable(t_minishell *mini, int *i, int start)
{
	char	*segment;
	char	*result;

	segment = ft_substr_safe(mini->cur_proc->cmd_seq, start, *i
			- start, mini);
	if (*segment == '\0')
	{
		free(segment);
		return (NULL);
	}
	if (!segment)
		return (NULL);
	if (ft_strchr(segment, '$'))
	{
		result = expansion(mini, segment);
		free(segment);
		if (!result)
			return (NULL);
		return (result);
	}
	return (segment);
}

int	handle_redirection(t_minishell *mini, int *i)
{
	if (mini->cur_proc->cmd_seq[*i] == '<'
		&& !is_between_quotes(mini->cur_proc->cmd_seq, *i))
	{
		if (!redin_heredoc_tokenizer(mini, i))
			return (-1);
		return (1);
	}
	else if (mini->cur_proc->cmd_seq[*i] == '>'
		&& !is_between_quotes(mini->cur_proc->cmd_seq, *i))
	{
		if (!redout_append_tokenizer(mini, i))
			return (-1);
		return (1);
	}
	return (0);
}

int	tokenize(t_minishell *mini)
{
	int		i;
	char	*cmd_seq;
	int		redir_result;

	i = 0;
	cmd_seq = mini->cur_proc->cmd_seq;
	while (cmd_seq[i])
	{
		redir_result = process_redirection(mini, &i);
		if (redir_result == 1)
			continue ;
		else if (redir_result == -1)
			return (0);
		else if (!process_word_or_space(mini, &i))
			return (0);
	}
	return (validate_redirects(mini));
}

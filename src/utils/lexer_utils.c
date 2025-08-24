/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:58:45 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/24 15:58:48 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	else if (is_cmd(segment, mini))
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

static int	handle_redirection(t_minishell *mini, int *i)
{
	if (mini->cur_proc->cmd_seq[*i] == '<'
		&& !is_between_quotes(mini->cur_proc->cmd_seq, *i))
	{
		if (!redin_heredoc_tokenizer(mini, i))
			return (0);
		return (1);
	}
	else if (mini->cur_proc->cmd_seq[*i] == '>'
		&& !is_between_quotes(mini->cur_proc->cmd_seq, *i))
	{
		if (!redout_append_tokenizer(mini, i))
			return (0);
		return (1);
	}
	return (0);
}

int	tokenize(t_minishell *mini)
{
	int		i;
	char	*cmd_seq;

	i = 0;
	cmd_seq = mini->cur_proc->cmd_seq;
	while (cmd_seq[i])
	{
		if (handle_redirection(mini, &i))
			continue ;
		else if (!ft_isspace(cmd_seq[i]))
		{
			word_tokenizer(mini, &i);
			continue ;
		}
		else
			skip_spaces(cmd_seq, &i);
	}
	return (1);
}

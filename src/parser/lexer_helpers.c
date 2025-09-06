/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 00:10:00 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/06 11:58:30 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_syntax_error(char *cmd_seq, int *i)
{
	if (cmd_seq[*i] == '\0')
	{
		write(2, "minishell: syntax error near unexpected token\n", 46);
		g_exit_status = 2;
		return (1);
	}
	return (0);
}

static char	*process_redir_string(t_minishell *mini, char *cmd_seq, int *i)
{
	char	*temp;

	if (cmd_seq[*i] == DOUBLE_QUOTE || cmd_seq[*i] == SINGLE_QUOTE)
	{
		temp = process_quoted_string(mini, cmd_seq, i);
		mini->cur_proc->heredoc_quote_flag = 1;
	}
	else
		temp = get_str(cmd_seq, i, mini);
	return (temp);
}

static char	*validate_redir_target(char *temp)
{
	if (temp && (ft_strchr(temp, '<') || ft_strchr(temp, '>')
			|| is_directory(temp)))
	{
		if (ft_strchr(temp, '<') || ft_strchr(temp, '>'))
		{
			write(2, "minishell: syntax error near unexpected token\n", 46);
			g_exit_status = 2;
		}
		free(temp);
		temp = NULL;
	}
	return (temp);
}

char	*get_redir_target(t_minishell *mini, int *i)
{
	char	*cmd_seq;
	char	*temp;

	cmd_seq = mini->cur_proc->cmd_seq;
	skip_spaces(cmd_seq, i);
	if (check_syntax_error(cmd_seq, i))
		return (NULL);
	if (!mini->cur_proc->heredoc_flag && !is_stopchar(cmd_seq[*i]))
		return (NULL);
	temp = process_redir_string(mini, cmd_seq, i);
	skip_spaces(cmd_seq, i);
	return (validate_redir_target(temp));
}

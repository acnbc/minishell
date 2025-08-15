/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:34:11 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/15 08:45:55 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*cut_double_quotes(t_minishell *mini, int i)
{
	char	*clean_input;
	char	*cmd_seq;
	int		j;

	clean_input = NULL;
	cmd_seq = mini->current_process->cmd_seq;
	j = i;
	while (cmd_seq[i] != DOUBLE_QUOTE && cmd_seq[i])
	{
		if (cmd_seq[i] == '$')
			clean_input = get_env_var(mini, cmd_seq, &i, &j);
		else
			i++;
	}
	if (j < i)
		clean_input = strjoin_free(clean_input, ft_substr_safe(cmd_seq, j, i
					- j, mini));
	return (clean_input);
}

static char	*cut_single_quotes(t_minishell *mini, int i)
{
	char	*clean_input;
	char	*cmd_seq;
	int		j;

	clean_input = NULL;
	cmd_seq = mini->current_process->cmd_seq;
	j = i;
	while (cmd_seq[i] != SINGLE_QUOTE && cmd_seq[i++])
		;
	clean_input = ft_substr_safe(cmd_seq, j, i - j, mini);
	return (clean_input);
}

char	*cut_quotes(t_minishell *mini, int *i, int *j, char quote)
{
	char	*clean_input;
	char	*cmd_seq;
	char	*temp;

	clean_input = NULL;
	cmd_seq = mini->current_process->cmd_seq;
	if (*j < *i)
		clean_input = strjoin_free(clean_input, ft_substr_safe(cmd_seq, *j,
					*i - *j, mini));
	if (quote == SINGLE_QUOTE)
	{
		temp = cut_single_quotes(mini, ++(*i));
		clean_input = strjoin_free(clean_input, temp);
		while (cmd_seq[*i] && cmd_seq[*i] != SINGLE_QUOTE)
			(*i)++;
	}
	else
	{
		temp = cut_double_quotes(mini, ++(*i));
		clean_input = strjoin_free(clean_input, temp);
		while (cmd_seq[*i] && cmd_seq[*i] != DOUBLE_QUOTE)
			(*i)++;
	}
	*j = ++(*i);
	return (clean_input);
}

char	*handle_quotes(t_minishell *mini, char *process, int *i)
{
	int		j;
	char	*clean_input;
	char	*temp;
	size_t	len;

	clean_input = NULL;
	j = *i;
	len = ft_strlen(process);
	while (*i < (int)len)
	{
		if ((process[*i] == '>' || process[*i] == '<' || process[*i] == '|')
			&& !is_between_quotes(process, *i))
			break ;
		if (process[*i] == SINGLE_QUOTE || process[*i] == DOUBLE_QUOTE)
		{
			temp = cut_quotes(mini, i, &j, process[*i]);
			clean_input = strjoin_free(clean_input, temp);
			continue ;
		}
		(*i)++;
	}
	return (clean_input);
}

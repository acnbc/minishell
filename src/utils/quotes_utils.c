/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:16:00 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/30 19:23:53 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_var_in_quotes(t_minishell *mini, char *cmd_seq, int *i, int *j)
{
	char	*clean_input;
	char	*temp;

	clean_input = NULL;
	while (cmd_seq[*i] != DOUBLE_QUOTE && cmd_seq[*i])
	{
		if (cmd_seq[*i] == '$')
		{
			temp = get_env_var(mini, cmd_seq, i, j);
			if (temp)
				clean_input = strjoin_free(clean_input, temp);
		}
		else
			(*i)++;
	}
	return (clean_input);
}

int	verify_quote_pair(char *input, char quote, int *i)
{
	int	flag;

	flag = 1;
	while (input[++(*i)] != quote && input[*i])
		;
	if (input[*i] == quote)
		flag = 0;
	return (flag);
}

int	verify_quote_count(char *process)
{
	int	single_flag;
	int	double_flag;
	int	i;

	single_flag = 0;
	double_flag = 0;
	i = -1;
	while (process[++i])
	{
		if (process[i] == SINGLE_QUOTE)
		{
			single_flag = verify_quote_pair(process, SINGLE_QUOTE, &i);
			if (single_flag % 2 == 0)
				return (1);
		}
		if (process[i] == DOUBLE_QUOTE)
		{
			double_flag = verify_quote_pair(process, DOUBLE_QUOTE, &i);
			if (double_flag % 2 == 0)
				return (1);
		}
		if (process[i] == '\0')
			break ;
	}
	return (0);
}

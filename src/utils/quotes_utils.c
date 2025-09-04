/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:16:00 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/04 08:29:26 by anogueir         ###   ########.fr       */
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
			// NÃO adicionar texto literal aqui - get_env_var já faz isso
			temp = get_env_var(mini, cmd_seq, i, j);
			if (temp)
				clean_input = strjoin_free(clean_input, temp);
		}
		else
			(*i)++;
	}
	// Adicionar texto literal restante
	if (*i > *j)
		clean_input = strjoin_free(clean_input,
			ft_substr_safe(cmd_seq, *j, *i - *j, mini));
	if (!clean_input)
		clean_input = ft_strdup("");
	return (clean_input);
}

int	verify_quote_pair(char *input, char quote, int *i)
{
	int	flag;

	flag = 0;
	while (input[++(*i)] != quote && input[*i])
		;
	if (input[*i] == quote)
		flag = 1;
	return (flag);
}

int	verify_quote_count(char *process)
{
	int	i;

	i = -1;
	while (process[++i])
	{
		if (process[i] == SINGLE_QUOTE)
		{
			if (!verify_quote_pair(process, SINGLE_QUOTE, &i))
				return (1);
		}
		if (process[i] == DOUBLE_QUOTE)
		{
			if (!verify_quote_pair(process, DOUBLE_QUOTE, &i))
				return (1);
		}
		if (process[i] == '\0')
			break ;
	}
	return (0);
}

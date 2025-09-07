/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:16:00 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/07 12:19:03 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

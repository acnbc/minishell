/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:45:20 by anogueir          #+#    #+#             */
/*   Updated: 2025/07/03 12:45:22 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_cmd_seq(t_process **phrases, char *input, int i, int j)
{
	char	*phrase;
	char	*temp;

	phrase = NULL;
	temp = NULL;
	temp = ft_substr(input, j, i - j);
	phrase = ft_strtrim(temp, " \t");
	free(temp);
	if (phrase && *phrase)
		add_process(phrases, new_process(phrase));
	else
		free(phrase);
}

t_process	*separate_process(char *input)
{
	int			i;
	int			j;
	int			double_quote_flag;
	t_process	*phrases;

	phrases = NULL;
	i = 0;
	skip_spaces(input, &i);
	j = i;
	double_quote_flag = 0;
	while (input[i])
	{
		if (input[i] == DOUBLE_QUOTE)
			double_quote_flag = !double_quote_flag;
		if (input[i] == '|' && !double_quote_flag)
		{
			if (i > j)
				get_cmd_seq(&phrases, input, i, j);
			j = ++i;
		}
		else
			i++;
	}
	if (i > j)
		get_cmd_seq(&phrases, input, i, j);
	return (phrases);
}

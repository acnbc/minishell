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
	int i;
	int j;
	t_process *phrases;
	
	i = 0;
	j = 0;
	phrases = NULL;
	while (input[i])
	{
		if (input[i] == '|' && !is_between_quotes(input, i))
		{
			if (i > j)
				get_cmd_seq(&phrases, input, i, j);
			i++;
			skip_spaces(input, &i);
			j = i;
		}
		else
			i++;
	}
	if (i > j)
		get_cmd_seq(&phrases, input, i, j);
	return (phrases);
}

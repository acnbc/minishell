/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:45:20 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/30 20:15:28 by anogueir         ###   ########.fr       */
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

static int	pipe_checks(char *input, int *i)
{
	int	j;

	j = *i;
	if (*i == 0 || input[*i + 1] == '\0')
	{
		write(2, "syntax error\n", 13);
		return (0);
	}
	j++;
	skip_spaces(input, &j);
	if (input[j] == '|' && j != *i)
	{
		write(2, "syntax error\n", 13);
		return (0);
	}
	return (1);
}

t_process	*separate_process(char *input)
{
	int			i;
	int			j;
	t_process	*phrases;

	i = 0;
	j = 0;
	phrases = NULL;
	while (input[i])
	{
		if (input[i] == '|' && !is_between_quotes(input, i))
		{
			if (!pipe_checks(input, &i))
				return (NULL);
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

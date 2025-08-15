/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:01:02 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/15 08:45:01 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_stopchar(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*extract_variable(t_minishell *mini, char *variable)
{
	t_env	*current;
	int		var_len;

	if (variable[0] == '?' && !is_stopchar(variable[1]))
	{
		free(variable);
		return (ft_itoa(g_exit_status));
	}
	current = mini->env_list;
	var_len = ft_strlen(variable);
	while (current)
	{
		if (ft_strncmp(current->var_name, variable, var_len + 1) == 0)
		{
			free(variable);
			return (ft_strdup(current->var_cont));
		}
		current = current->next;
	}
	free(variable);
	return (NULL);
}

char	*get_env_var(t_minishell *mini, char *segment, int *i, int *j)
{
	char	*var_name;
	char	*expanded;
	int		start;

	if (!mini || !segment || !i || !j)
		return (NULL);
	*j = ++(*i);
	if (segment[*i] == '?')
	{
		var_name = ft_strdup("?");
		(*i)++;
	}
	else
	{
		start = *i;
		while (segment[*i] && is_stopchar(segment[*i]))
			(*i)++;
		var_name = ft_substr(segment, start, *i - start);
	}
	*j = *i;
	expanded = extract_variable(mini, var_name);
	return (expanded);
}

char	*expansion(t_minishell *mini, char *segment)
{
	char	*clean;
	char	*var_value;
	int		i;
	int		j;

	clean = NULL;
	i = 0;
	j = 0;
	while (segment[i])
	{
		if (segment[i] == '$')
		{
			if (j < i)
				clean = strjoin_free(clean, ft_substr(segment, j, i - j));
			var_value = get_env_var(mini, segment, &i, &j);
			if (var_value)
				clean = strjoin_free(clean, var_value);
			j = i;
		}
		else
			i++;
	}
	if (j < i)
		clean = strjoin_free(clean, ft_substr(segment, j, i - j));
	return (clean);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:01:02 by anogueir          #+#    #+#             */
/*   Updated: 2025/06/17 12:01:04 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_stopchar(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*extract_variable(t_minishell *minishell, char *variable)
{
	t_env	*current;
	int		var_len;

	if (variable[0] == '?' && !is_stopchar(variable[1]))
	{
		free(variable);
		return (ft_itoa(g_exit_status));
	}
	current = minishell->env_list;
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

/*char	*get_env_var(t_minishell *minishell, char *segment, int *i, int *j)
{
	char	*clean_input;

	if (!minishell || !minishell->current_process->cmd_seq || !i || !j)
		return (NULL);
	clean_input = NULL;
	if (*j < *i)
		clean_input = ft_strjoin_free(clean_input, ft_substr(segment, *j, *i
					- *j));
	*j = ++(*i);
	while (segment[*i] && is_stopchar(segment[*i]))
		(*i)++;
	clean_input = ft_strjoin_free(clean_input, extract_variable(minishell,
				ft_substr(segment, *j, *i - *j)));
	*j = *i;
	return (clean_input);
}

char	*expansion(t_minishell *minishell, char *segment)
{
	char	*clean_input;
	int		i;
	int		j;

	clean_input = NULL;
	i = 0;
	j = i;
	while (segment[i])
	{
		if (segment[i] == '$')
			clean_input = get_env_var(minishell, segment, &i, &j);
		else
			i++;
	}
	if (j < i)
		clean_input = ft_strjoin_free(clean_input, ft_substr(segment, j, i
					- j));
	return (clean_input);
}*/

char	*get_env_var(t_minishell *minishell, char *segment, int *i, int *j)
{
	char	*var_name;
	char	*expanded;

	if (!minishell || !segment || !i || !j)
		return (NULL);

	*j = ++(*i); // pula o '$'

	if (segment[*i] == '?')
	{
		var_name = ft_strdup("?");
		(*i)++;
	}
	else
	{
		int start = *i;
		while (segment[*i] && is_stopchar(segment[*i]))
			(*i)++;
		var_name = ft_substr(segment, start, *i - start);
	}

	*j = *i;
	expanded = extract_variable(minishell, var_name);
	return expanded;
}


char	*expansion(t_minishell *minishell, char *segment)
{
	char	*clean_input = NULL;
	char	*var_value;
	int		i = 0;
	int		j = 0;

	while (segment[i])
	{
		if (segment[i] == '$')
		{
			if (j < i)
				clean_input = ft_strjoin_free(clean_input, ft_substr(segment, j, i - j));
			var_value = get_env_var(minishell, segment, &i, &j);
			if (var_value)
				clean_input = ft_strjoin_free(clean_input, var_value);
			j = i;
		}
		else
			i++;
	}
	if (j < i)
		clean_input = ft_strjoin_free(clean_input, ft_substr(segment, j, i - j));
	return (clean_input);
}

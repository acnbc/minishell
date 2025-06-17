/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:01:02 by anogueir          #+#    #+#             */
/*   Updated: 2025/06/17 12:01:04 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_stopchar(char c)
{
	return (ft_isspace(c) || c == SINGLE_QUOTE || c == DOUBLE_QUOTE || c == '$'
		|| c == '\0');
}

static char	*extract_variable(t_minishell *minishell, char *variable)
{
	char	*var_extracted;
	char	*equal_sign;
	int		i;
	int		var_len;

	var_extracted = NULL;
	equal_sign = NULL;
	var_len = ft_strlen(variable);
	i = -1;
	while (minishell->envp_copy[++i])
	{
		if (ft_strncmp(minishell->envp_copy[i], variable, var_len) == 0)
		{
			equal_sign = ft_strchr(minishell->envp_copy[i], '=');
			if (equal_sign)
			{
				free(variable);
				return (ft_strdup(equal_sign + 1));
			}
		}
	}
	free(variable);
	return (NULL);
}

// Verificar variável envolvida por áspa dupla
char	**eansion(char **strings, t_minishell *minishell, int max_strings)
{
	t_eansion	e;

	ft_bzero(&e, sizeof(t_eansion));
	while (minishell->input[e.i] && e.str_i < max_strings)
	{
		if (minishell->input[e.i] == '$' && minishell->input[e.i + 1]
			&& !is_stopchar(minishell->input[e.i + 1]))
		{
			if (e.i > e.start)
				strings[e.str_i++] = ft_substr(minishell->input, e.start, e.i
						- e.start);
			e.start = e.i++;
			while (!is_stopchar(minishell->input[e.i]))
				e.i++;
			var_name = ft_substr(minishell->input, e.start, e.i - e.start);
			strings[str_i++] = extract_variable(minishell, var_name);
			e.start = e.j;
		}
		else
			e.i++;
		if (minishell->input[e.start] && e.str_i < max_strings)
			strings[epx.str_i++] = ft_substr(minishell->input, e.start, e.i
					- e.start);
		strings[e.str_i] = NULL;
	}
	return (strings);
}

char	**variable_eansion(t_minishell *minishell)
{
	int var_count;
	int non_var;
	int i;
	char **strings;

	strings = NULL;
	var_count = 0;
	non_var = 0;
	i = -1;
	while (minishell->input[++i])
	{
		if (minishell->input[i] == '$' && minishell->input[i + 1]
			&& !ft_isspace(minishell->input[i + 1]))
			;
		{
			var_count++;
			if (i != 0)
				non_var++;
		}
	}
	strings = (char **)safe_malloc(sizeof(char *) * (var_count + non_var + 2));
	return (strings = eansion(minishell, var_count + non_var));
}
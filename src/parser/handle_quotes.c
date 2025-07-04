/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:34:11 by anogueir          #+#    #+#             */
/*   Updated: 2025/06/12 19:34:12 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*static char	*cut_double_quotes(t_minishell *minishell, int i)
{
	char	*clean_input;
	int		j;

	clean_input = NULL;
	j = i;
	while (minishell->input[i] != DOUBLE_QUOTE && minishell->input[i])
	{
		if (minishell->input[i] == '$')
			clean_input = get_env_var(minishell, &i, &j);
		else
			i++;
	}
	if (j < i)
		clean_input = ft_strjoin_free(clean_input, ft_substr(minishell->input,
					j, i - j));
	return (clean_input);
}

static char	*cut_single_quotes(t_minishell *minishell, int i)
{
	char	*clean_input;
	int		j;

	clean_input = NULL;
	j = i;
	while (minishell->input[i] != SINGLE_QUOTE && minishell->input[i++])
		;
	return (ft_substr(minishell->input, j, i - j));
}

static int	verify_quote_pair(char *input, char quote, int *i)
{
	int	flag;

	flag = 1;
	while (input[++(*i)] != quote && input[*i])
		;
	if (input[*i] == quote)
		flag = 0;
	return (flag);
}

static int	verify_quote_count(t_minishell *minishell)
{
	int	single_flag;
	int	double_flag;
	int	i;

	if (!minishell || !minishell->input)
		return (1);
	single_flag = 0;
	double_flag = 0;
	i = -1;
	while (minishell->input[++i])
	{
		if (minishell->input[i] == SINGLE_QUOTE)
			single_flag = verify_quote_pair(minishell->input, SINGLE_QUOTE, &i);
		if (minishell->input[i] == DOUBLE_QUOTE)
			double_flag = verify_quote_pair(minishell->input, DOUBLE_QUOTE, &i);
	}
	return (single_flag + double_flag);
}

char	*cut_quotes(t_minishell *minishell, int *i, int *j, char quote)
{
	char	*clean_input;
	char	*temp;

	clean_input = NULL;
	if (*j < *i)
	{
		temp = ft_substr(minishell->input, *j, *i - *j);
		clean_input = ft_strjoin_free(clean_input, temp);
	}
	if (quote == SINGLE_QUOTE)
	{
		temp = cut_single_quotes(minishell, ++(*i));
		clean_input = ft_strjoin_free(clean_input, temp);
		while (minishell->input[*i] && minishell->input[*i] != SINGLE_QUOTE)
			(*i)++;
	}
	else
	{
		temp = cut_double_quotes(minishell, ++(*i));
		clean_input = ft_strjoin_free(clean_input, temp);
		while (minishell->input[*i] && minishell->input[*i] != DOUBLE_QUOTE)
			(*i)++;
	}
	*j = *i + 1;
	return (clean_input);
}

char	*handle_quotes(t_minishell *minishell)
{
	int		i;
	int		j;
	char	*clean_input;
	char	*temp;

	clean_input = NULL;
	if (verify_quote_count(minishell))
		return (NULL);
	j = 0;
	i = -1;
	while (minishell->input[++i])
	{
		if (minishell->input[i] == SINGLE_QUOTE
			|| minishell->input[i] == DOUBLE_QUOTE)
		{
			temp = cut_quotes(minishell, &i, &j, minishell->input[i]);
			clean_input = ft_strjoin_free(clean_input, temp);
		}
	}
	if (j < i)
	{
		temp = ft_substr(minishell->input, j, i - j);
		clean_input = ft_strjoin_free(clean_input, temp);
	}
	return (clean_input);
}*/

//	em handle_quotes.c:
//		retirar a expansão de variável de cut_double_quote
//		alterar cut_double_quote para remover aspas duplas da mesma forma que cut_single_quote remove aspas simples

static char	*cut_double_quotes(t_minishell *minishell, int i)
{
	char	*clean_input;
	int		j;

	clean_input = NULL;
	j = i;
	while (minishell->current_process[i] != DOUBLE_QUOTE && minishell->current_process[i])
	{
		if (minishell->current_process[i] == '$')
			clean_input = get_env_var(minishell, &i, &j);
		else
			i++;
	}
	if (j < i)
		clean_input = ft_strjoin_free(clean_input, ft_substr_safe(minishell->current_process,
					j, i - j, minishell));
	return (clean_input);
}

static char	*cut_single_quotes(t_minishell *minishell, int i)
{
	char	*clean_input;
	int		j;

	clean_input = NULL;
	j = i;
	while (minishell->current_process[i] != SINGLE_QUOTE && minishell->current_process[i++])
		;
	clean_input = ft_substr_safe(minishell->current_process, j, i - j, minishell);
	return (clean_input);
}

char	*cut_quotes(t_minishell *minishell, int *i, int *j, char quote)
{
	char	*clean_input;
	char	*temp;

	clean_input = NULL;
	if (*j < *i)
		clean_input = ft_strjoin_free(clean_input, ft_substr_safe(minishell->current_process, *j, *i - *j, minishell));
	if (quote == SINGLE_QUOTE)
	{
		temp = cut_single_quotes(minishell, ++(*i));
		clean_input = ft_strjoin_free(clean_input, temp);
		while (minishell->current_process[*i] && minishell->current_process[*i] != SINGLE_QUOTE)
			(*i)++;
	}
	else
	{
		temp = cut_double_quotes(minishell, ++(*i));
		clean_input = ft_strjoin_free(clean_input, temp);
		while (minishell->current_process[*i] && minishell->current_process[*i] != DOUBLE_QUOTE)
			(*i)++;
	}
	*j = *i + 1;
	return (clean_input);
}

static int	verify_quote_pair(char *input, char quote, int *i)
{
	int	flag;

	flag = 1;
	while (input[++(*i)] != quote && input[*i])
		;
	if (input[*i] == quote)
		flag = 0;
	return (flag);
}

static int	verify_quote_count(char *process)
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
	}
	return (0);
}

char	*handle_quotes(t_minishell *minishell, char *process)
{
	int		i;
	int		j;
	char	*clean_input;
	char	*temp;

	clean_input = NULL;
	if (!verify_quote_count(process))
		return (NULL);
	j = 0;
	i = -1;
	minishell->current_process = process;
	while (process[++i])
	{
		if (process[i] == SINGLE_QUOTE || process[i] == DOUBLE_QUOTE)
		{
			temp = cut_quotes(minishell, &i, &j, process[i]);
			clean_input = ft_strjoin_free(clean_input, temp);
		}
	}
	if (j < i)
		clean_input = ft_strjoin_free(clean_input, ft_substr_safe(process, j, i - j, minishell));
	return (clean_input);
}
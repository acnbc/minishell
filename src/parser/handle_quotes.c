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

static char	*handle_double_quotes(t_minishell *minishell, int i)
{
	char	*clean_input;
	int		j;
	
	clean_input = NULL;
	j = i;
	while (minishell->input[i] != DOUBLE_QUOTE && minishell->input[i])
	{
		if (minishell->input[i] == '$')
		{
			if (j < i)
				clean_input = ft_strjoin(clean_input, ft_substr(minishell->input, j, i - j));
			j = ++i;
			while (minishell->input[i] && ft_isalnum(minishell->input[i]) && minishell->input[i] != DOUBLE_QUOTE)
				i++;
			clean_input = ft_strjoin(clean_input, extract_variable(minishell, ft_substr(minishell->input, j, i - j)));
			j = i;
		}
		else
			i++;
	}
	if (j < i)
        clean_input = ft_strjoin(clean_input, ft_substr(minishell->input, j, i - j));
    return (clean_input);
}

static char	*handle_single_quotes(t_minishell *minishell, int i)
{
	char	*clean_input;
	int		j;
	
	clean_input = NULL;
	j = i;
	while (minishell->input[i] != SINGLE_QUOTE && minishell->input[i++])
		;
	clean_input = safe_malloc((i + 1) * sizeof(char));
	clean_input = ft_substr(minishell->input, j, i - j);
	return (clean_input);
}

static int		verify_quote_pair(char *input, char quote, int *i)
{
	int flag;
	
	flag = 1;
	while(input[++(*i)] != quote && input[*i])
		;
	if (input[*i] == quote)
		flag = 0;
	return (flag);
}
static int		verify_quote_count(t_minishell *minishell)
{
	int	single_flag;
	int	double_flag;
	int	i;

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

char	*handle_quotes(t_minishell *minishell)
{
	int				i;
	int				j;
	char			*clean_input;

	i = -1;
	j = 0;
	clean_input = NULL;
	if (verify_quote_count(minishell))
		return (NULL);
	while (minishell->input[++i])
	{
		if (minishell->input[i] == SINGLE_QUOTE)
		{
			if (j < i)
				clean_input = ft_strjoin(clean_input, ft_substr(minishell->input, j, i - j));
			clean_input = ft_strjoin(clean_input, handle_single_quotes(minishell, ++i));
			while (minishell->input[i] && minishell->input[i] != SINGLE_QUOTE)
            	i++;
			j = i + 1;
		}
		else if (minishell->input[i] == DOUBLE_QUOTE)
		{
			if (j < i)
				clean_input = ft_strjoin(clean_input, ft_substr(minishell->input, j, i - j));
			clean_input = ft_strjoin(clean_input, handle_double_quotes(minishell, ++i));
			while (minishell->input[i] && minishell->input[i] != DOUBLE_QUOTE)
            	i++;
			j = i + 1;
		}
	}
	if (j < i)
		clean_input = ft_strjoin(clean_input, ft_substr(minishell->input, j, i - j));
	return (clean_input);
}

// Verificar se cada abertura de aspas tem uma a aspas de fechamento correspondente
// Se não tiver, retornar NULL
// Iterar sobre a string de entrada
// Se abrir uma aspa simples,
// 		usar ft_substr para copiar o que veio até ali e chamar handle_single_quotes
// 		copiar todo o conteúdo até encontrar a próxima aspa simples
// 		retornar o nó de string sem aspa simples
// Se abrir uma aspa dupla,
// 		usar ft_substr para copiar o que veio até ali e chamar handle_double_quotes
// 		copiar todo o conteúdo até encontrar a próxima aspa dupla
// 		Se encontrar um caractere $,
// 			copiar tudo que veio até ali e chamar variable_expansion
// 			Se a variável existir,
//				retornar o conteúdo da variável
// 			Se não existir,
// 				retornar NULL
// 		dar join no que foi copiado até $ e a variável expandida
// 		retornar o nó de string sem aspa dupla
// Dar join no que foi copiado até abrir aspas e o conteúdo retornado de handle_single_quotes ou handle_double_quotes	
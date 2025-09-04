/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:11:57 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/04 08:29:26 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Função auxiliar: processa conteúdo entre aspas simples (tudo literal).
*/
static char	*process_single_quotes(const char *seg, int *j)
{
	int		start;
	int		k;

	(*j)++;
	start = *j;
	k = *j;
	while (seg[k] && seg[k] != SINGLE_QUOTE)
		k++;
	*j = k;
	if (seg[*j] == SINGLE_QUOTE)
		(*j)++;
	return (ft_substr(seg, start, k - start));
}

/*
** Função auxiliar: processa conteúdo entre aspas duplas (literal + variáveis).
*/
static char	*process_double_quotes(t_minishell *mini, const char *seg, int *j)
{
	char	*res;
	int		start;
	int		k;

	res = NULL;
	(*j)++;
	while (seg[*j] && seg[*j] != DOUBLE_QUOTE)
	{
		if (seg[*j] == '$')
		{
			k = *j + 1;
			if (seg[k] == '?')
				k++;
			else
				while (seg[k] && is_stopchar(seg[k]))
					k++;
			res = strjoin_free(res, expansion(mini, ft_substr(seg, *j, k - *j)));
			*j = k;
		}
		else
		{
			start = *j;
			while (seg[*j] && seg[*j] != DOUBLE_QUOTE && seg[*j] != '$')
				(*j)++;
			res = strjoin_free(res, ft_substr(seg, start, *j - start));
		}
	}
	if (seg[*j] == DOUBLE_QUOTE)
		(*j)++;
	if (!res)
		res = ft_strdup("");
	return (res);
}

/*
** Função auxiliar: expande variáveis do tipo $VAR ou $?
*/
static char	*expand_variable(t_minishell *mini, const char *segment, int *j)
{
	int	k;
	char	*var;
	char	*val;

	k = *j + 1;
	if (segment[k] == '?')
		k++;
	else
		while (segment[k] && is_stopchar(segment[k]))
			k++;
	var = ft_substr(segment, *j, k - *j);
	val = expansion(mini, var);
	*j = k;
	return (val);
}

/*
** Função auxiliar: expande texto literal até encontrar aspas ou variável.
*/
static char	*expand_literal(const char *segment, int *j)
{
	int	k;
	char	*literal;

	k = *j;
	while (segment[k] && segment[k] != SINGLE_QUOTE &&
		segment[k] != DOUBLE_QUOTE && segment[k] != '$')
		k++;
	literal = ft_substr(segment, *j, k - *j);
	*j = k;
	return (literal);
}

/*
** Função auxiliar: expande o conteúdo de um segmento.
*/
static char	*expand_segment(t_minishell *mini, const char *segment)
{
	char	*expanded;
	int		j;

	expanded = NULL;
	j = 0;
	while (segment[j])
	{
		if (segment[j] == SINGLE_QUOTE)
			expanded = strjoin_free(expanded,
				process_single_quotes(segment, &j));
		else if (segment[j] == DOUBLE_QUOTE)
			expanded = strjoin_free(expanded,
				process_double_quotes(mini, segment, &j));
		else if (segment[j] == '$')
			expanded = strjoin_free(expanded,
				expand_variable(mini, segment, &j));
		else
			expanded = strjoin_free(expanded,
				expand_literal(segment, &j));
	}
	if (!expanded)
		expanded = ft_strdup("");
	return (expanded);
}

/*
** Função auxiliar: cria o token apropriado baseado no conteúdo.
*/
static void	create_token(t_minishell *mini, char *expanded)
{
	t_token	**tokens;

	tokens = &mini->cur_proc->tokens;
	if (!*tokens)
	{
		if (is_builtin(expanded))
			token_lstadd_back(tokens, new_token(expanded, BUILTIN, mini));
		else if (!mini->cur_proc->path && is_cmd(expanded, mini))
			token_lstadd_back(tokens, new_token(expanded, CMD, mini));
		else
			token_lstadd_back(tokens, new_token(expanded, ARGS, mini));
	}
	else
		token_lstadd_back(tokens, new_token(expanded, ARGS, mini));
}

/*
** Função principal: tokeniza e expande um segmento de comando.
*/
void	word_tokenizer(t_minishell *mini, int *i)
{
	char	*cmd_seq;
	int		start;
	int		len;
	char	*segment;
	char	*expanded;

	cmd_seq = mini->cur_proc->cmd_seq;
	start = *i;
	len = ft_strlen(cmd_seq);
	while (*i < len)
	{
		if (ft_isspace(cmd_seq[*i]) ||
			((cmd_seq[*i] == '>' || cmd_seq[*i] == '<') &&
			!is_between_quotes(cmd_seq, *i)))
			break ;
		(*i)++;
	}
	if (*i > start)
	{
		segment = ft_substr(cmd_seq, start, *i - start);
		expanded = expand_segment(mini, segment);
		create_token(mini, expanded);
		free(segment);
	}
}

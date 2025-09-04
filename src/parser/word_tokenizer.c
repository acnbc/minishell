/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:11:57 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/04 08:52:19 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Funções de processamento de aspas movidas para src/utils/quote_processor.c */

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
		if ((ft_isspace(cmd_seq[*i]) && !is_between_quotes(cmd_seq, *i)) ||
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

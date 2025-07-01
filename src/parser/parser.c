/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:37:33 by anogueir          #+#    #+#             */
/*   Updated: 2025/06/12 19:37:34 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parser(t_minishell *minishell)
{
	t_process	*lex_ready;

	lex_ready = NULL;
	if (ft_strchr(minishell->input, DOUBLE_QUOTE))
		lex_ready = separate_process(handle_quotes(minishell));
	else if (ft_strchr(minishell->input, SINGLE_QUOTE))
		lex_ready = separate_process(handle_quotes(minishell));
	else if (ft_strchr(minishell->input, '$'))
		lex_ready = separate_process(expansion(minishell));
	else
		lex_ready = separate_process(minishell->input);
	if (!lex_ready)
		return ;
	print_process_list(lex_ready);
	free_process_list(lex_ready);
}

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
	char		*processed_input;
	t_process	*lexer_ready;

	if (!minishell || !minishell->input)
		return ;
	lexer_ready = NULL;
	if (ft_strchr(minishell->input, DOUBLE_QUOTE) || ft_strchr(minishell->input,
			SINGLE_QUOTE))
		processed_input = handle_quotes(minishell);
	else if (ft_strchr(minishell->input, '$'))
		processed_input = expansion(minishell);
	else
		processed_input = minishell->input;
	if (processed_input)
	{
		lexer_ready = separate_process(processed_input);
		if (processed_input != minishell->input)
			free(processed_input);
	}
	if (lexer_ready)
	{
		if (minishell->process_list)
			free_process_list(minishell->process_list);
		minishell->process_list = lexer_ready;
		print_process_list(lexer_ready);
	}
}

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
	minishell->process_list = separate_process(minishell->input);
	if (!minishell->process_list)
		return ;
	minishell->process_count = count_process(minishell->process_list);
	printf("process_count: %d\n", minishell->process_count);
	lexer(minishell);
	if (syntactic_analysis(minishell) == false)
		return ;
	print_process_list(minishell->process_list);
}

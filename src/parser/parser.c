/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:37:33 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/15 08:41:22 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parser(t_minishell *mini)
{
	mini->process_list = separate_process(mini->input);
	if (!mini->process_list)
		return (0);
	if (!lexer(mini))
		return (0);
	handle_heredoc(mini);
	if (syntactic_analysis(mini) == false)
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:37:33 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/06 13:08:13 by anogueir         ###   ########.fr       */
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
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:15:13 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/18 19:39:15 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write (1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		rl_done = 1;
	}
}

int	mini_shell(t_minishell *mini)
{
	if (!mini)
		return (0);
	mini->input = readline(MINISHELL_PROMPT);
	if (!mini->input)
		safe_exit(mini);
	if (ft_strncmp(mini->input, "exit", 5) == 0)
		safe_exit(mini);
	if ((ft_strchr(mini->input, DOUBLE_QUOTE)
			|| ft_strchr(mini->input, SINGLE_QUOTE))
		&& !verify_quote_count(mini->input))
	{
		free(mini->input);
		return (1);
	}
	if (!parser(mini))
	{
		flush(mini);
		return (0);
	}
	executor(mini);
	unlink_heredoc_files(mini);
	add_history(mini->input);
	return (1);
}

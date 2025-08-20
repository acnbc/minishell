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

static void	ft_exit(t_minishell *mini)
{
	char			*input;
	
	input = ft_strtrim(mini->input, " \t\n\v\f\r");
	if (ft_strncmp(input, "exit", 4) == 0 && (input[4] == '\0'
		|| ft_isspace(input[4])))
    {
        write(1, "exit\n", 5);
        safe_exit(mini);
    }
	return ;
}


static char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		if (str[i] == to_find[j])
		{
			while ((to_find[j] != '\0') && (str[i + j] == to_find[j]))
				j++;
			if (to_find[j] == '\0')
				return (&str[i]);
		}
		i++;
	}
	return (NULL);
}

int	mini_shell(t_minishell *mini)
{
	if (!mini)
		return (0);
	mini->input = readline(MINISHELL_PROMPT);
	if (!mini->input)
		safe_exit(mini);
	if (ft_strstr(mini->input, "exit"))
		ft_exit(mini);
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

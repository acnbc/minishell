/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 16:00:28 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/24 16:08:28 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*put_line_break(char *line)
{
	char	*tmp;

	tmp = ft_strjoin(line, "\n");
	if (!tmp)
		safe_exit(NULL);
	free(line);
	line = tmp;
	return (line);
}

void	write_heredoc_line(int fd, char *line, t_minishell *mini)
{
	if (write(fd, line, ft_strlen(line)) < 0)
	{
		perror("heredoc write");
		free(line);
		safe_exit(mini);
	}
}

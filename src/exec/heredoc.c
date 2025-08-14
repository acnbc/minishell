/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:21:34 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/11 19:21:37 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*put_line_break(char *line)
{
	char	*tmp;

	tmp = ft_strjoin(line, "\n");
	if (!tmp)
		safe_exit(NULL);
	free(line);
	line = tmp;
	return (line);
}

void	unlink_heredoc_files(t_minishell *minishell)
{
	t_process	*current;
	char		*filename;

	current = minishell->process_list;
	while (current)
	{
		if (current->heredoc_flag && current->input_file)
		{
			filename = current->input_file;
			if (unlink(filename) == -1)
				perror("unlink");
			free(filename);
			current->input_file = NULL;
		}
		current = current->next;
	}
}

static void	here_doc(t_minishell *mini)
{
	int			fd;
	char		*line;
	char		*temp;
	char		*filename;
	t_process	*p;

	p = mini->current_process;
	filename = ft_itoa(p->process_num);
	if (!filename)
		safe_exit(mini);
	fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (!fd)
	{
		perror("heredoc open");
		safe_exit(mini);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, p->heredoc_delimiter,
				ft_strlen(p->heredoc_delimiter)) == 0)
		{
			free(line);
			break ;
		}
		line = put_line_break(line);
		if (!line)
			safe_exit(mini);
		if (p->heredoc_quote_flag)
		{
			temp = expansion(mini, line);
			free(line);
			if (!temp)
			{
				perror("heredoc expansion");
				safe_exit(mini);
			}
			line = temp;
		}
		if (write(fd, line, ft_strlen(line)) < 0)
		{
			perror("heredoc write");
			free(line);
			safe_exit(mini);
		}
		if (ft_strlen(line) == 0)
		{
			free(line);
			continue ;
		}
		free(line);
	}
	close(fd);
	p->input_file = filename;
}

void	handle_heredoc(t_minishell *mini)
{
	t_process *p;

	p = mini->process_list;
	while (p)
	{
		if (p->heredoc_flag)
		{
			mini->current_process = p;
			here_doc(mini);
		}
		p = p->next;
	}
}

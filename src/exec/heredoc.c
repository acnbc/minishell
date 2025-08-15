/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:21:34 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/15 09:10:16 by anogueir         ###   ########.fr       */
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

void	unlink_heredoc_files(t_minishell *mini)
{
	t_process	*current;
	char		*filename;

	current = mini->process_list;
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

static int	open_heredoc_file(char *filename, t_minishell *mini)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("heredoc open");
		safe_exit(mini);
	}
	return (fd);
}

static char	*process_line(t_minishell *mini, t_process *p, char *line)
{
	char	*temp;

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
	line = put_line_break(line);
	if (!line)
		safe_exit(mini);
	return (line);
}

static void	write_heredoc_line(int fd, char *line, t_minishell *mini)
{
	if (write(fd, line, ft_strlen(line)) < 0)
	{
		perror("heredoc write");
		free(line);
		safe_exit(mini);
	}
}

static void	here_doc(t_minishell *mini)
{
	char		*line;
	char		*filename;
	t_process	*p;

	p = mini->cur_proc;
	filename = ft_itoa(p->process_num);
	if (!filename)
		safe_exit(mini);
	p->heredoc_fd = open_heredoc_file(filename, mini);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, p->delimiter, ft_strlen(p->delimiter)) == 0)
		{
			free(line);
			break ;
		}
		line = process_line(mini, p, line);
		write_heredoc_line(p->heredoc_fd, line, mini);
		free(line);
	}
	close(p->heredoc_fd);
	p->input_file = filename;
}

void	handle_heredoc(t_minishell *mini)
{
	t_process	*p;
	int			i;

	i = 1;
	p = mini->process_list;
	while (p)
	{
		p->process_num = i;
		if (p->heredoc_flag)
		{
			mini->cur_proc = p;
			here_doc(mini);
		}
		p = p->next;
		i++;
	}
}

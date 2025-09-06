/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 23:45:00 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/06 17:59:44 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	setup_builtin_redirects(t_process *p)
{
	if (p->fdin != -1 && p->fdin != 0)
		dup2(p->fdin, 0);
	if (p->fdout != -1 && p->fdout != 1)
		dup2(p->fdout, 1);
}

void	restore_builtin_redirects(t_process *p)
{
	if (p->fdin != -1 && p->fdin != 0)
	{
		close(p->fdin);
		p->fdin = -1;
	}
	if (p->fdout != -1 && p->fdout != 1)
	{
		close(p->fdout);
		p->fdout = -1;
	}
}

int	is_directory(char *word)
{
	struct stat	path_stat;

	if (stat(word, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			write(2, "minishell: ", 11);
			write(2, word, ft_strlen(word));
			write(2, ": Is a directory\n", 18);
			g_exit_status = 126;
			return (1);
		}
	}
	return (0);
}

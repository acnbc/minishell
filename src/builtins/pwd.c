/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:24:47 by abouchat          #+#    #+#             */
/*   Updated: 2025/09/06 15:43:12 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_output_fd(t_process *p)
{
	if (p->fdout == -1)
		return (1);
	return (p->fdout);
}

int	ft_pwd(t_process *p)
{
	char	buffer[4096];
	char	*cwd;
	int		fd;

	cwd = getcwd(buffer, sizeof(buffer));
	if (!cwd)
		return (1);
	fd = get_output_fd(p);
	write(fd, cwd, ft_strlen(cwd));
	write(fd, "\n", 1);
	return (0);
}

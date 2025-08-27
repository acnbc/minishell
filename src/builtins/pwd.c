/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:24:47 by abouchat          #+#    #+#             */
/*   Updated: 2025/08/27 10:41:22 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_process *p)
{
	char	buffer[4096];
	char	*cwd;

	cwd = getcwd(buffer, sizeof(buffer));
	if (!cwd)
		return (1);
	
	write(p->fdout, cwd, ft_strlen(cwd));
	write(p->fdout, "\n", 1);
	return (0);
}

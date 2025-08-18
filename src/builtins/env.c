/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:46:54 by abouchat          #+#    #+#             */
/*   Updated: 2025/08/18 15:29:12 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_env *env_list, int fd)
{
	t_env	*curr;

	curr = env_list;
	while (curr)
	{
		write(fd, curr->var_name, ft_strlen(curr->var_name));
		write(fd, "=", 1);
		write(fd, curr->var_cont, ft_strlen(curr->var_cont));
		write(fd, "\n", 1);
		curr = curr->next;
	}
	return (EXIT_SUCCESS);
}

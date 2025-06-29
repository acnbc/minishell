/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:46:54 by abouchat          #+#    #+#             */
/*   Updated: 2025/06/29 16:56:49 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_env_node *env_cpy)
{
	t_env_node	*curr;

	curr = env_cpy;
	while (curr)
	{
		write(1, curr->var, ft_strlen(curr->var));
		write(1, "\n", 1);
		curr = curr->next;
	}
}


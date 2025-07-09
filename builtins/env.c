/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:46:54 by abouchat          #+#    #+#             */
/*   Updated: 2025/07/09 17:01:52 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_env *env_list)
{
	t_env	*curr;

	curr = env_list;
	while (curr)
	{
		write(1, curr->var_name, ft_strlen(curr->var_name));
		write(1, "=", 1);
		write(1, curr->var_cont, ft_strlen(curr->var_cont));
		write(1, "\n", 1);
		curr = curr->next;
	}
}


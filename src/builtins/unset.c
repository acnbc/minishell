/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:31:22 by abouchat          #+#    #+#             */
/*   Updated: 2025/09/06 19:00:35 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(t_env *env_list, char **args)
{
	t_env	*curr;
	t_env	*temp;

	while (++args && *args)
	{
		if (!find_env_var(*args, env_list))
			continue ;
		curr = find_env_var(*args, env_list);
		temp = curr->prev;
		temp->next = curr->next;
		if (temp->next != NULL)
			temp->next->prev = temp;
		curr->next = NULL;
		curr->prev = NULL;
		free(curr->var_cont);
		free(curr->var_name);
		free(curr);
	}
	return (EXIT_SUCCESS);
}

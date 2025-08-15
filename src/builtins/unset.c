/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:31:22 by abouchat          #+#    #+#             */
/*   Updated: 2025/07/09 18:54:48 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(char *var, t_env *env_list)
{
	t_env	*curr;
	t_env	*temp;

	if (!find_env_var(var, env_list))
		return ;
	curr = find_env_var(var, env_list);
	temp = curr->prev;
	temp->next = curr->next;
	if (temp->next != NULL)
		temp->next->prev = temp;
	curr->next = NULL;
	curr->prev = NULL;
	free_env_list(curr);
}

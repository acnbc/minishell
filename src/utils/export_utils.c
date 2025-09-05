/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 16:13:58 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/05 08:31:06 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*find_env_var(char *var, t_env *env_list)
{
	t_env	*curr;

	curr = env_list;
	while (curr)
	{
		if (ft_strlen(var) == ft_strlen(curr->var_name)
			&& !ft_strncmp(var, curr->var_name, ft_strlen(var)))
			break ;
		curr = curr->next;
	}
	return (curr);
}

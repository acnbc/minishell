/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 16:13:58 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/26 15:24:53 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*find_env_var(char *var, t_env *env_list)
{
	t_env	*curr;
	size_t	len;

	curr = env_list;
	len = 0;
	while (curr)
	{
		if (ft_strlen(var) >= ft_strlen(curr->var_name))
			len = ft_strlen(var);
		else
			len = ft_strlen(curr->var_name);
		if (!ft_strncmp(var, curr->var_name, len))
			break ;
		curr = curr->next;
	}
	return (curr);
}

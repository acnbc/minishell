/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:24:47 by abouchat          #+#    #+#             */
/*   Updated: 2025/08/18 15:27:49 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_process *p, t_env *env_list)
{
	t_env	*curr;

	curr = find_env_var("PWD", env_list);
	if (!curr)
		return (1);
	write(p->fdout, curr->var_cont, ft_strlen(curr->var_cont));
	write(p->fdout, "\n", 1);
	return (0);
}

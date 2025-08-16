/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:24:47 by abouchat          #+#    #+#             */
/*   Updated: 2025/08/16 12:36:19 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_process *p, t_env *env_list)
{
	t_env	*curr;

	curr = find_env_var("PWD", env_list);
	if (!curr)
		return (1);
	write(1, curr->var_cont, ft_strlen(curr->var_cont));
	write(1, "\n", 1);
	if (p->output_file)
		write(p->fdout, "0\n", 2);
	return (0);
}

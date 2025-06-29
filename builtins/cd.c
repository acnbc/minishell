/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:42:44 by abouchat          #+#    #+#             */
/*   Updated: 2025/06/29 16:03:53 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(char *str, t_shelldata *env_vars)
{
// 1. and 2.
	if (!str || !str[0])
	{
		if (!(env_vars-> home_path))
			return ;
		else
			
	}
}


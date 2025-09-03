/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:40:31 by abouchat          #+#    #+#             */
/*   Updated: 2025/09/03 17:03:38 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// bash: exit: too many arguments -> 1
// bash: exit: numeric argument required -> 2

static int	numerical_check(char *str)
{
	
}

int	ft_exit(t_minishell *mini, char **args)
{
	int	exit_status;

	if (args[1] == NULL)
		return (EXIT_SUCCESS);
	if (!numerical_check(args[1]))
	{
		write(2, "exit: numeric argument required\n", 33);
		return (2);
	}
	if (args[2])
	{
		write(2, "exit: too many arguments\n", 26);
		return (1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 17:58:37 by abouchat          #+#    #+#             */
/*   Updated: 2025/08/17 16:10:21 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	verify_flag(char *str)
{
	if (*str != '-')
		return (false);
	str++;
	while (*str)
	{
		if (*str != 'n')
			return (false);
		str++;
	}
	return (true);
}

int	ft_echo(char **args, int fd)
{
	int	flag;

	flag = 1;
	while (verify_flag(*args))
	{
		flag = 0;
		args++;
	}
	while (*args)
	{
		write(fd, *args, ft_strlen(*args));
		if (*(args + 1) != NULL)
			write(fd, " ", 1);
		args++;
	}
	if (flag == 1)
		write(fd, "\n", 1);
	return (EXIT_SUCCESS);
}

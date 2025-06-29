/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 17:58:37 by abouchat          #+#    #+#             */
/*   Updated: 2025/06/29 15:11:10 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	ft_echo(char **args, int fd)
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
}


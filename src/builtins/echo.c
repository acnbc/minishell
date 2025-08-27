/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 17:58:37 by abouchat          #+#    #+#             */
/*   Updated: 2025/08/27 09:53:43 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	verify_flag(char *str)
{
	if (!str)
		return (false);
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
	int	i;

	flag = 1;
	i = 0;
	if (args[i + 1])
	{
		while (verify_flag(args[++i]))
			flag = 0;
		if (args[i])
		{
			while (args[i])
			{
				write(fd, args[i], ft_strlen(args[i]));
				if (args[i + 1] != NULL)
					write(fd, " ", 1);
				i++;
			}
		}
	}
	if (flag == 1)
		write(fd, "\n", 1);
	return (EXIT_SUCCESS);
}

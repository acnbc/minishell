/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:40:31 by abouchat          #+#    #+#             */
/*   Updated: 2025/09/03 21:52:32 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static long long int	ft_atoll(const char *nptr)
{
	long long int	res;
	long int		neg;

	if (nptr == NULL)
		return (0);
	res = 0;
	neg = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
	{
		neg = neg * (-1);
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
		res = (res * 10) + (*nptr++ - '0');
	return (res * neg);
}

static int	numerical_check(char *str)
{
	long long int	num;
	size_t			i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		i++;
	else if (str[i] == '+')
		i++;
	if (!str[i])
		return (-1);
	while (i < ft_strlen(str))
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	num = ft_atoll(str);
	if (num > LLONG_MAX || num < LLONG_MIN)
	{
		return (-1);
	}
	return ((unsigned char)num);
}

int	ft_exit(char **args)
{
	int	exit_status;

	write(1, "exit\n", 6);
	if (args[1] == NULL)
		return (EXIT_SUCCESS);
	if (numerical_check(args[1]) < 0)
	{
		write(2, "exit: numeric argument required\n", 33);
		return (2);
	}
	if (args[2])
	{
		write(2, "exit: too many arguments\n", 26);
		return (1);
	}
	exit_status = numerical_check(args[1]);
	return (exit_status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 17:58:37 by abouchat          #+#    #+#             */
/*   Updated: 2025/06/19 16:16:17 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char **args, int fd, int flag)
{
//	int	arg_c;
//	arg_c = 0;
	while(*args)
	{
//		arg_c++;
		write(fd, *args, ft_strlen(*args));
		args++
	}
	if (flag = 1)
		write(fd, "\n", 1);
}


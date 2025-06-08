/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:13:18 by abouchat          #+#    #+#             */
/*   Updated: 2024/10/03 12:25:53 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	nb;
	char		res;

	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = nb * (-1);
	}
	if (nb >= 10)
		ft_putnbr_fd(nb / 10, fd);
	res = (nb % 10) + '0';
	write(fd, &res, 1);
}

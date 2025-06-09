/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:35:30 by abouchat          #+#    #+#             */
/*   Updated: 2024/10/03 19:11:37 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	num_len(long int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void	ft_attribute(int n_len, long int n, char *num)
{
	int	i;

	i = n_len - 1;
	while (n != 0)
	{
		num[i--] = '0' + (n % 10);
		n = n / 10;
	}
}

char	*ft_itoa(int n)
{
	int			n_len;
	char		*num;
	long int	long_n;

	long_n = n;
	n_len = num_len(long_n);
	if (long_n < 0)
	{
		n_len = n_len + 1;
		num = (char *)malloc(sizeof(char) * n_len + 1);
		num[0] = '-';
		long_n = long_n * (-1);
	}
	else
		num = (char *)malloc(sizeof(char) * n_len + 1);
	if (!num)
		return (NULL);
	if (long_n == 0)
		num[0] = '0';
	else
		ft_attribute(n_len, long_n, num);
	num[n_len] = '\0';
	return (num);
}
/*
int	main(void)
{
	char *num = ft_itoa(25);

	write(1, num, 2);
}*/
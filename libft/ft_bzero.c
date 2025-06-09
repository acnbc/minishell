/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:57:44 by abouchat          #+#    #+#             */
/*   Updated: 2024/10/03 12:24:55 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*c;

	c = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		*(c + i) = '\0';
		i++;
	}
}
/*
int	main(void)
{
	char	str2[10] = "salve";

	//char str1[5] = "salve";
	//ft_bzero(str1, 5);
	//write(1, str1, 5);
	write(1, "\n", 1);
	bzero(str2, 5);
	write(1, str2, );
}
*/

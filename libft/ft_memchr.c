/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:44:01 by abouchat          #+#    #+#             */
/*   Updated: 2024/10/03 15:29:47 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	if (s == NULL)
		return (NULL);
	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return ((void *)(str + i));
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	#include <stdio.h>
	#include <string.h>
	//char	*str = "salve";
	char	*char_found1;
	//char	*char_found2;

	char_found1 = ft_memchr(NULL, -10, 5);
	//char_found2 = memchr(NULL, -10, 5);
	if(char_found1 == NULL)
		write(1, "char1 is NULL\n", 15);
	else
	{
		printf("\n%p\n", char_found1);
		write(1, char_found1, 1);
	}
	// if(char_found2 == NULL)
	// 	write(1, "char2 is NULL\n", 15);
	// else
	// {
	// 	printf("\n%p\n", char_found2);
	// 	write(1, char_found2, 1);
	// }

}*/
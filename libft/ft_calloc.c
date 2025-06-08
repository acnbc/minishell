/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:02:43 by abouchat          #+#    #+#             */
/*   Updated: 2024/10/14 12:52:57 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	if (nmemb > 9223372036854775807 || size > 9223372036854775807)
		return (NULL);
	ptr = (unsigned char *)malloc(size * nmemb);
	if (!ptr)
		return (NULL);
	while (i < nmemb * size)
		ptr[i++] = 0;
	return ((void *)ptr);
}
/*
int	main(void)
{
	#include <unistd.h>
	void	*ptr1;
	void	*ptr2;

	ptr1 = ft_calloc(-1, -1);
	ptr2 = calloc(-1, -1);

	if(ptr1 == NULL)
		write(1, "ptr1 NULL", 10);
		if(!ptr2)
		{
		write(1, "ptr2 NULL", 10);
		}
	if(ptr1 && ptr2)
	{
	write(1, ptr1, 1);
	write(1, "\n", 1);
	write(1, ptr2, 1);
	}
}*/
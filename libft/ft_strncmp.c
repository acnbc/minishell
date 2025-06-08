/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:03:19 by abouchat          #+#    #+#             */
/*   Updated: 2024/10/03 15:58:36 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] < s2[i] || s1[i] > s2[i])
			return (s1[i] - s2[i]);
		else
			i++;
	}
	return (0);
}
/*
int	main(void)
{
	#include <stdio.h>
	#include <string.h>
	char	*str1 = "salve";
	char	*str2 = "zalve";

	printf("%d\n", ft_strncmp(str1, str2, 0));
	printf("%d\n", strncmp(str1, str2, 0));

}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:59:26 by abouchat          #+#    #+#             */
/*   Updated: 2024/10/14 11:38:37 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = ft_strlen(s);
	if (start > s_len)
	{
		substr = ft_calloc(1, sizeof(char));
		return (substr);
	}
	if (len >= s_len)
	{
		len = s_len;
		substr = (char *)malloc(sizeof(char) * (len - start) + 1);
	}
	else
		substr = (char *)malloc(sizeof(char) * len + 1);
	if (!substr)
		return (NULL);
	while (i < len && s[start] != '\0')
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}
/*
int	main(void)
{
	char	str1[10] = "salvetropa";
	char	*str2;

	str2 = ft_substr(str1, 0, 20);
	if (str2 == NULL)
		write(1, "NULL", 4);
	write(1, str2, 10);
}*/
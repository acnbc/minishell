/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 21:28:27 by abouchat          #+#    #+#             */
/*   Updated: 2024/10/03 15:37:38 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, char const *s2)
{
	char	*str;
	int		s1_len;
	int		s2_len;
	int		i;

	if (!s1)
		s1_len = 0;
	else
		s1_len = ft_strlen(s1);
	if (!s2)
		s2_len = 0;	
	else
		s2_len = ft_strlen(s2);
	i = -1;
	str = malloc(sizeof(char) * ((s1_len + s2_len) + 1));
	if (!str)
		return (NULL);
	while (++i < s1_len)
		str[i] = s1[i];
	i = -1;
	while (++i < s2_len)
		str[s1_len + i] = s2[i];
	str[s1_len + s2_len] = '\0';
	return (str);
}
/*
int	main(void)
{
	char	s1[10] = "salve ";
	char	s2[10] = "tropa";
	char	*s3;

	s3 = ft_strjoin(s1, s2);
	write(1, s3, (ft_strlen(s3) + 1));
	write(1, "\n", 1);
}*/

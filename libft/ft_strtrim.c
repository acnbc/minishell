/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:16:51 by abouchat          #+#    #+#             */
/*   Updated: 2024/10/14 11:19:47 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_in_set(char *str, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0' && *str != '\0')
	{
		if (*str == set[i++])
			return (1);
	}
	return (0);
}

static void	find_len(char const *s1, char const *set, size_t *i, size_t *s1_len)
{
	while (find_in_set((char *)(s1 + (*i)), set))
		(*i)++;
	while (find_in_set((char *)(s1 + ((*s1_len) - 1)), set))
		(*s1_len)--;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	s1_len;
	size_t	i;
	size_t	j;

	if (s1 == NULL || set == NULL)
		return (NULL);
	j = 0;
	i = 0;
	s1_len = ft_strlen(s1);
	find_len(s1, set, &i, &s1_len);
	if (s1_len < i)
	{
		str = ft_calloc(1, sizeof(char));
		return (str);
	}
	str = (char *)malloc(sizeof(char) * (s1_len - i) + 1);
	if (!str)
		return (NULL);
	while (i < s1_len)
		str[j++] = s1[i++];
	str[j] = '\0';
	return (str);
}
/*
int	main(void)
{
	char *s1 = "xxxzzz   xxx";
	char *s2 = " xz";
	char *str_final;

	str_final = ft_strtrim(s1, s2);
	if (str_final == NULL)
		write(1, "NULL", 4);
	write(1, str_final, (ft_strlen(str_final) + 1));
	write (1, "\n", 1);
}*/
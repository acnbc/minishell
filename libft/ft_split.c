/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:28:11 by abouchat          #+#    #+#             */
/*   Updated: 2025/03/18 17:43:57 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	split_free(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		arr[i] = NULL;
		i--;
	}
	free(arr);
}

int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	if (s[0] == '\0')
		return (0);
	count = 0;
	while (s[i] == c)
		i++;
	if (s[i] != '\0')
		count = 1;
	while (s[i] != '\0')
	{
		if (s[i] == c && (s[i + 1] != c && s[i + 1] != '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	*find_word(char const *s, char c, int *i)
{
	int		start;
	int		j;
	char	*str;

	j = 0;
	while (s[*i] == c)
		(*i)++;
	start = *i;
	while (s[*i] != c && s[*i] != '\0')
		(*i)++;
	str = (char *)malloc(sizeof(char) * (*i - start) + 1);
	while (s[start] == c)
		start++;
	while (s[start] != c && s[start] != '\0')
		str[j++] = s[start++];
	str[j] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**split_arr;
	int		arr_len;
	int		arr_i;
	int		i;

	arr_len = count_words(s, c);
	split_arr = (char **)malloc(sizeof(char *) * (arr_len + 1));
	if (!split_arr)
		return (NULL);
	arr_i = 0;
	i = 0;
	while (arr_i < arr_len)
	{
		split_arr[arr_i] = find_word(s, c, &i);
		if (!split_arr[arr_i])
		{
			split_free(split_arr, arr_i);
			split_arr = NULL;
			return (split_arr);
		}
		arr_i++;
	}
	split_arr[arr_len] = NULL;
	return (split_arr);
}
/*
int	main(void)
{
	#include <string.h>
	#include <stdio.h>
	char	*str;
	char	**arr;

	str = strdup(",,,,,,,,,,salve,,,,,tropa,kkkk,,,,,,");
	arr = ft_split(str, ',');
	for (size_t i = 0; i < 4; i++)
	{
		if (arr[i] == NULL)
			printf("NULL\n");
		else
		{
			printf("%s\n", arr[i]);
			free (arr[i]);
		}
	}
	free (arr);
	free (str);
}
*/
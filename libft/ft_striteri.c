/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:54:34 by abouchat          #+#    #+#             */
/*   Updated: 2024/10/08 23:35:05 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// static void	next_char(unsigned int i, char *s)
// {
// 	*s = *s + i;
// }

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

// int	main(void)
// {
// 	char str[10] = "0000000000";

// 	write(1, str, 10);
// 	write(1, "\n", 1);
// 	ft_striteri(str, next_char);
// 	write(1, str, 10);
// }
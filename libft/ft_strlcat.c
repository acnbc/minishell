/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:41:34 by abouchat          #+#    #+#             */
/*   Updated: 2024/10/14 12:10:54 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	i = 1;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	if (!src || !src[i])
		return (dst_len);
	if (size < dst_len)
		return (src_len + size);
	while (i < size - dst_len && src[i - 1] != '\0')
	{
		dst[i + dst_len - 1] = src[i - 1];
		i++;
	}
	dst[i + dst_len] = '\0';
	if (size > dst_len)
		return (dst_len + src_len);
	return (src_len + size);
}
/*
int	main(void)
{
	char	dest1[50] = "ab";
	char	src1[50] = "cde";
	char	dest2[50] = "ab";
	char	src2[50] = "cde";

	printf("\nMEU: %ld\n", ft_strlcat(dest1, src1, 1));
	write(1, dest1, ft_strlen(dest1) + 1);
	printf("\nESPERADO: %ld\n", strlcat(dest2, src2, 1));
	write(1, dest1, ft_strlen(dest2) + 1);

	printf("\nMEU: %ld\n", ft_strlcat(dest1, src1, 5));
	write(1, dest1, ft_strlen(dest1) + 1);
	printf("\nESPERADO: %ld\n", strlcat(dest2, src2, 5));
	write(1, dest1, ft_strlen(dest2) + 1);

	printf("\nMEU: %ld\n", ft_strlcat(dest1, src1, 3));
	write(1, dest1, ft_strlen(dest1) + 1);
	printf("\nESPERADO: %ld\n", strlcat(dest2, src2, 3));
	write(1, dest1, ft_strlen(dest2) + 1);

	printf("\nMEU: %ld\n", ft_strlcat(dest1, src1, 6));
	write(1, dest1, ft_strlen(dest1) + 1);
	printf("\nESPERADO: %ld\n", strlcat(dest2, src2, 6));
	write(1, dest1, ft_strlen(dest2) + 1);
}*/
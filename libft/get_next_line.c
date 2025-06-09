/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:56:52 by abouchat          #+#    #+#             */
/*   Updated: 2025/05/04 17:02:53 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_func(char **ptr1, char **ptr2, char **ptr3)
{
	if (ptr1)
	{
		free(*ptr1);
		*ptr1 = NULL;
	}
	if (ptr2)
	{
		free(*ptr2);
		*ptr2 = NULL;
	}
	if (ptr3)
	{
		free(*ptr3);
		*ptr3 = NULL;
	}
}

static char	*stash_check(char **stash, int *index, char *out)
{
	char	*aux;
	char	*bef_stash;

	aux = NULL;
	if (!*stash)
		out = gnl_strdup("");
	else if (gnl_strchr(*stash, '\n') == -1)
	{
		aux = out;
		out = gnl_strdup(*stash);
		free_func(stash, NULL, NULL);
	}
	else if ((gnl_strchr(*stash, '\n') >= 0))
	{
		*index = gnl_strchr(*stash, '\n');
		*index = (unsigned int)*index;
		bef_stash = gnl_substr(*stash, 0, *index + 1);
		aux = *stash;
		*stash = gnl_substr(*stash, *index + 1,
				(gnl_strlen(*stash) - (*index + 1)));
		out = gnl_strdup(bef_stash);
		free_func(&bef_stash, NULL, NULL);
	}
	free_func(&aux, NULL, NULL);
	return (out);
}

static char	*buf_check(char *buf, char *out, int *index, char **stash)
{
	char	*aux;
	char	*bef_stash;

	if (gnl_strchr(buf, '\n') == -1)
	{
		aux = out;
		out = gnl_strjoin(out, buf);
	}
	else
	{
		*index = (unsigned int)*index;
		*index = gnl_strchr(buf, '\n');
		aux = *stash;
		*stash = gnl_substr(buf, *index + 1, (gnl_strlen(buf) - (*index + 1)));
		free_func(&aux, NULL, NULL);
		bef_stash = gnl_substr(buf, 0, *index + 1);
		aux = out;
		out = gnl_strjoin(out, bef_stash);
		free_func(&bef_stash, NULL, NULL);
	}
	free_func(&aux, NULL, NULL);
	return (out);
}

static char	*read_loop(char *buf, char *out, char **stash, int fd)
{
	size_t	bytes_read;
	int		index;

	bytes_read = 0;
	index = -1;
	bytes_read = read(fd, buf, BUFFER_SIZE);
	if ((int)bytes_read == -1)
	{
		free_func(NULL, &out, NULL);
		return (NULL);
	}
	buf[bytes_read] = '\0';
	out = buf_check(buf, out, &index, stash);
	while (bytes_read > 0 && index == -1)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		buf[bytes_read] = '\0';
		out = buf_check(buf, out, &index, stash);
	}
	return (out);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*out;
	char		*buf;
	int			index;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		split_free(stash, 1023);
		return (NULL);
	}
	index = -1;
	out = NULL;
	i = 0;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (i < BUFFER_SIZE)
		buf[i++] = 0;
	out = stash_check(&stash[fd], &index, out);
	if (index == -1)
		out = read_loop(buf, out, &stash[fd], fd);
	if (out && !out[0])
		free_func(&out, NULL, NULL);
	free_func(&buf, NULL, NULL);
	return (out);
}

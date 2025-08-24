/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:48:34 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/24 14:12:23 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dup2_safe(t_minishell *mini, int *fd, int dup2_fd,
		const char *error_message)
{
	dup2(*fd, dup2_fd);
	if (*fd == -1)
	{
		perror(error_message);
		safe_exit(mini);
	}
}

void	dup_safe(t_minishell *mini, int *fd, int dup_fd,
		const char *error_message)
{
	*fd = dup(dup_fd);
	if (*fd == -1)
	{
		perror(error_message);
		safe_exit(mini);
	}
}

char	*ft_substr_safe(char *s, unsigned int start, size_t len,
		t_minishell *mini)
{
	char	*substr;

	substr = ft_substr(s, start, len);
	if (!substr)
		safe_exit(mini);
	return (substr);
}

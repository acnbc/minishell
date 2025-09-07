/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:48:34 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/07 18:15:19 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_substr_safe(char *s, unsigned int start, size_t len,
		t_minishell *mini)
{
	char	*substr;

	substr = ft_substr(s, start, len);
	if (!substr)
		safe_exit(mini);
	return (substr);
}

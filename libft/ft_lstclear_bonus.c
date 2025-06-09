/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:31:30 by abouchat          #+#    #+#             */
/*   Updated: 2024/10/14 11:06:47 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*aux;

	if (!lst)
	{
		lst = NULL;
		return ;
	}
	if (!del)
		return ;
	curr = *lst;
	while (curr)
	{
		aux = curr;
		del(curr->content);
		curr = curr->next;
		free(aux);
	}
	*lst = NULL;
}

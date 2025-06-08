/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 10:39:52 by abouchat          #+#    #+#             */
/*   Updated: 2024/10/07 14:56:20 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULL)
		return ;
	if (lst == NULL)
	{
		lst = &new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}
/*
int	main(void)
{
	int	val2;
	int	val1;
  t_list *curr;

	#include <stdio.h>
  t_list *node1, *node2;
  val2 = 2;
  val1 = 1;
  node2 = ft_lstnew(&val2);
  node1 = ft_lstnew(&val1);
  ft_lstadd_front(&node2, node1);
  curr = node1;
  while (curr != NULL)
  {
	printf("%d\n", *((int *)curr->content));
	curr = curr->next;
  }
}
*/
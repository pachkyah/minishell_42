/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypachkou <ypachkou@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 22:00:35 by pachkyah          #+#    #+#             */
/*   Updated: 2025/06/23 17:29:05 by ypachkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
/*
    This function adds the node ’new’ at the beginning of the list.
*/
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

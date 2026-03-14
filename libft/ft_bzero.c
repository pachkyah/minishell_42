/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypachkou <ypachkou@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:24:33 by ypachkou          #+#    #+#             */
/*   Updated: 2025/06/25 14:02:35 by ypachkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Sets a block of memory to zero.
 *
 * This function writes zero bytes to the first @p n bytes of the memory
 * area pointed to by @p ptr. It is typically used to initialize memory
 * to zero.
 *
 * @param ptr Pointer to the memory area to zero out.
 * @param n Number of bytes to set to zero.
 */
void	ft_bzero(void *ptr, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = ptr;
	i = 0;
	while (i < n)
	{
		p[i++] = 0;
	}
}

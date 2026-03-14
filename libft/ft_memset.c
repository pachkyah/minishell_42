/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypachkou <ypachkou@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:25:12 by ypachkou          #+#    #+#             */
/*   Updated: 2025/06/25 14:04:50 by ypachkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Fills a block of memory with a specific byte value.
 * 
 * Sets the first @p n bytes of the memory area pointed to by @p ptr
 * to the byte value @p val (converted to unsigned char).
 *
 * @param ptr Pointer to the memory area to fill.
 * @param val Byte value to set.
 * @param n Number of bytes to fill.
 * @return Pointer to the memory area @p ptr.
 */
void	*ft_memset(void *ptr, int val, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = ptr;
	i = 0;
	while (i < n)
	{
		p[i++] = (unsigned char)val;
	}
	return (ptr);
}

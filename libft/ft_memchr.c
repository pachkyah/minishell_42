/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypachkou <ypachkou@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:25:03 by ypachkou          #+#    #+#             */
/*   Updated: 2025/06/25 14:04:40 by ypachkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Searches for a byte in a memory block.
 * 
 * Scans the first @p n bytes of the memory area pointed to by @p s
 * for the first occurrence of the byte @p c. The search does not
 * stop at null bytes or newline characters!!!
 *
 * @param s Pointer to the memory area to search.
 * @param c Byte to search for (interpreted as unsigned char).
 * @param n Number of bytes to scan.
 * @return Pointer to the matching byte, or NULL if not found.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;
	size_t				i;

	ptr = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return ((void *)(ptr + i));
		i++;
	}
	return (NULL);
}

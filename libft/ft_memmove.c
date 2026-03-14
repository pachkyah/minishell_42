/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypachkou <ypachkou@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:25:10 by ypachkou          #+#    #+#             */
/*   Updated: 2025/06/25 14:04:47 by ypachkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Helper function for forward memory copy.
 * 
 * Copies @p n bytes from @p s to @p d in increasing memory address order.
 *
 * @param d Destination pointer.
 * @param s Source pointer.
 * @param n Number of bytes to copy.
 */
static void	memmove_forward(unsigned char *d, const unsigned char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
}

/**
 * @brief Helper function for backward memory copy.
 *
 * Copies @p n bytes from @p s to @p d in decreasing memory address order.
 *
 * @param d Destination pointer.
 * @param s Source pointer.
 * @param n Number of bytes to copy.
 */
static void	memmove_backward(unsigned char *d, const unsigned char *s, size_t n)
{
	while (n > 0)
	{
		n--;
		d[n] = s[n];
	}
}

/**
 * @brief Copies bytes between potentially overlapping memory areas.
 *
 * Copies @p n bytes from memory area @p src to memory area @p dest.
 * The copy is performed safely even if the memory areas overlap,
 * by choosing the appropriate copy direction.
 *
 * @param dest Pointer to the destination memory area.
 * @param src Pointer to the source memory area.
 * @param n Number of bytes to copy.
 * @return Pointer to the destination memory area @p dest.
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d == s || n == 0)
	{
		return (dest);
	}
	if (d < s)
		memmove_forward(d, s, n);
	else
		memmove_backward(d, s, n);
	return (dest);
}

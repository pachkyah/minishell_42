/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypachkou <ypachkou@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:24:40 by ypachkou          #+#    #+#             */
/*   Updated: 2025/06/25 14:02:41 by ypachkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates zero-initialized memory for an array.
 *
 * Allocates memory for an array of @p num elements of @p size bytes each,
 * and sets all bytes to zero. Returns NULL if the allocation fails or if
 * an integer overflow occurs.
 *
 * @param num Number of elements to allocate.
 * @param size Size of each element in bytes.
 * @return Pointer to the allocated memory, or NULL on failure.
 */
void	*ft_calloc(size_t num, size_t size)
{
	size_t	total_size;
	void	*ptr;

	total_size = num * size;
	if (size != 0 && total_size / size != num)
	{
		return (NULL);
	}
	ptr = (void *)malloc(total_size);
	if (ptr == NULL)
	{
		return (NULL);
	}
	return (ft_memset(ptr, 0, total_size));
}

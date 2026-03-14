/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypachkou <ypachkou@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:25:39 by ypachkou          #+#    #+#             */
/*   Updated: 2025/06/25 14:10:49 by ypachkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Appends src string to the end of dest string.
 * 
 * Appends the string @p src to the end of @p dest, ensuring that
 * the total length does not exceed @p size. The resulting string
 * is null-terminated if @p size is greater than 0.
 *
 * @param dest The destination buffer.
 * @param src The source string to append.
 * @param size The full size of the destination buffer.
 * @return The total length of the string it tried to create
 * (initial length of dest plus length of src).
 */
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = 0;
	if (size <= dst_len)
		return (size + src_len);
	while (src[i] && (dst_len + i) < size - 1)
	{
		dest[dst_len + i] = src[i];
		i++;
	}
	dest[dst_len + i] = '\0';
	return (dst_len + src_len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypachkou <ypachkou@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:25:29 by ypachkou          #+#    #+#             */
/*   Updated: 2025/06/25 14:10:28 by ypachkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Finds the first occurrence of a character in a string.
 * 
 * Searches the string @p str for the first occurrence of the character @p c,
 * scanning from left to right. The terminating null byte is considered part
 * of the string.
 *
 * @param str The string to search.
 * @param c The character to find (converted to char).
 * @return Pointer to the first occurrence of @p c in @p str,
 * or NULL if not found.
 */
char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (c == '\0')
		return ((char *)str);
	return (NULL);
}

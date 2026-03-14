/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypachkou <ypachkou@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:11:32 by ypachkou          #+#    #+#             */
/*   Updated: 2025/06/25 14:11:50 by ypachkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Finds the last occurrence of a character in a string.
 * 
 * Searches the string @p str for the last occurrence of the character @p c,
 * scanning from right to left. The terminating null byte is considered part
 * of the string.
 *
 * @param str The string to search.
 * @param c The character to find (converted to char).
 * @return Pointer to the last occurrence of @p c in @p str,
 * or NULL if not found.
 */
char	*ft_strrchr(const char *str, int c)
{
	const char	*last = NULL;

	while (*str)
	{
		if (*str == (char)c)
			last = str;
		str++;
	}
	if (c == '\0')
		return ((char *)str);
	return ((char *)last);
}

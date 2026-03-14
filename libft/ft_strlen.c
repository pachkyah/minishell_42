/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypachkou <ypachkou@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:25:44 by ypachkou          #+#    #+#             */
/*   Updated: 2025/06/25 14:05:24 by ypachkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Calculates the length of a string.
 * 
 * Counts and returns the number of characters in the string @p str,
 * excluding the terminating null byte.
 *
 * @param str The string to measure.
 * @return The length of the string.
 */
size_t	ft_strlen(const char *str)
{
	const char	*s;

	s = str;
	while (*(s++))
	{
	}
	return (s - str - 1);
}

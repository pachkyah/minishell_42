/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypachkou <ypachkou@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:25:00 by ypachkou          #+#    #+#             */
/*   Updated: 2025/06/25 14:03:06 by ypachkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Calculates the number of digits in an integer.
 * 
 * Helper function that returns the number of digits required
 * to represent @p n as a string, including space for the minus sign
 * if the number is negative.
 *
 * @param n The integer to evaluate.
 * @return Number of digits in @p n.
 */
static size_t	int_len(int n)
{
	size_t	len;
	long	num;

	if (n <= 0)
		len = 1;
	else
		len = 0;
	num = n;
	if (num < 0)
		num = -num;
	while (num != 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

/**
 * @brief Converts an integer to a string.
 *
 * Allocates and returns a null-terminated string representing
 * the integer @p n. Handles negative numbers and edge cases
 * such as INT_MIN.
 *
 * @param n The integer to convert.
 * @return Pointer to the resulting string, or NULL on failure.
 */
char	*ft_itoa(int n)
{
	size_t	len;
	char	*str;
	long	num;

	num = n;
	len = int_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (num == 0)
		str[0] = '0';
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	while (num > 0)
	{
		str[--len] = '0' + (num % 10);
		num /= 10;
	}
	return (str);
}

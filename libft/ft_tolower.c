/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypachkou <ypachkou@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:26:02 by ypachkou          #+#    #+#             */
/*   Updated: 2025/06/25 14:05:46 by ypachkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Converts an uppercase letter to lowercase.
 * 
 * If @p c is an uppercase letter, converts it to its lowercase equivalent.
 * Otherwise, returns @p c unchanged.
 *
 * @param c The character to convert.
 * @return The lowercase equivalent if uppercase, otherwise @p c.
 */
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + ('a' - 'A'));
	return (c);
}

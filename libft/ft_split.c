/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypachkou <ypachkou@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:25:26 by ypachkou          #+#    #+#             */
/*   Updated: 2025/06/25 14:05:03 by ypachkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Counts the number of words separated by a delimiter.
 * 
 * Helper function that counts how many substrings are separated
 * by the character @p c in the string @p s.
 *
 * @param s The input string.
 * @param c The delimiter character.
 * @return The number of words found.
 */
static size_t	word_count(const char *s, char c)
{
	size_t	count;
	int		in_word;

	in_word = 0;
	count = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

/**
 * @brief Frees allocated memory for an array of strings.
 *
 * Helper function that frees @p i elements in the array @p arr,
 * used to clean up memory on failure.
 *
 * @param arr The array of strings to free.
 * @param i The number of elements to free.
 */
static void	free_all(char **arr, size_t i)
{
	while (i--)
		free(arr[i]);
	free(arr);
}

/**
 * @brief Extracts the next word from a string.
 *
 * Helper function that returns a newly allocated string containing
 * the next word in @p s starting at @p *index, using @p c as delimiter.
 * Updates @p *index to the position after the extracted word.
 *
 * @param s The input string.
 * @param c The delimiter character.
 * @param index Pointer to the current index in @p s.
 * @return Newly allocated string containing the next word.
 */
static char	*next_word(const char *s, char c, size_t *index)
{
	size_t	start;
	size_t	end;

	start = *index;
	while (s[start] == c)
		start++;
	end = start;
	while (s[end] && s[end] != c)
		end++;
	if (end > start)
	{
		*index = end;
		return (ft_substr(s, start, end - start));
	}
	*index = end;
	return (NULL);
}

/**
 * @brief Splits a string into an array of strings using a delimiter.
 *
 * Allocates memory and returns a NULL-terminated array of strings
 * obtained by splitting the string @p s using the character @p c as
 * a delimiter.
 *
 * @param s The string to split.
 * @param c The delimiter character.
 * @return A NULL-terminated array of strings, or NULL on allocation failure.
 */
char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	new_start;
	size_t	i;
	size_t	w_count;

	new_start = 0;
	i = 0;
	if (!s)
		return (NULL);
	w_count = word_count(s, c);
	res = malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!res)
		return (NULL);
	while (i < w_count)
	{
		res[i] = next_word(s, c, &new_start);
		if (!res[i])
		{
			free_all(res, i);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypachkou <ypachkou@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 01:07:10 by ypachkou          #+#    #+#             */
/*   Updated: 2026/01/11 01:35:27 by ypachkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Extracts the next line from the stash.
 * 
 * Scans the stash for the first newline character ('\n') and returns
 * a newly allocated string containing the line, including the newline
 * if present. If the stash is empty, returns NULL.
 *
 * @param stash The string containing the buffered data.
 * @return A newly allocated string with the extracted line, or NULL on failure.
 */
static char	*extract_line(char *stash)
{
	int		i;
	char	*line;

	if (!stash || !*stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = ft_substr(stash, 0, i);
	if (!line)
		return (NULL);
	return (line);
}

/**
 * @brief Concatenates two strings into a new string.
 * 
 * Allocates memory and returns a new string which is the concatenation
 * of @p s1 and @p s2.
 * For get_next_line deletes the first string @p s1 
 *
 * @param s1 The first string.
 * @param s2 The second string.
 * @return Pointer to the newly allocated concatenated string,
 * or NULL on failure.
 */
static char	*gnl_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*joined;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!joined)
		return (NULL);
	ft_memcpy(joined, s1, len1);
	ft_memcpy(joined + len1, s2, len2);
	joined[len1 + len2] = '\0';
	free(s1);
	return (joined);
}

/**
 * @brief Cleans the stash after extracting a line.
 * 
 * Removes the extracted line from the stash and returns a new string
 * containing the remaining data. Frees the old stash. If no data remains,
 * returns NULL.
 *
 * @param stash The current stash string.
 * @return A newly allocated string with the remaining data,
 * or NULL if empty or on failure.
 */
static char	*clean_stash(char *stash)
{
	int		i;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_strdup(&stash[i + 1]);
	if (!new_stash)
	{
		free(stash);
		return (NULL);
	}
	free(stash);
	return (new_stash);
}

/**
 * @brief Reads from the file descriptor
 * into the stash until a newline is found or EOF.
 * 
 * Allocates a buffer and repeatedly reads BUFFER_SIZE
 * bytes from the given file descriptor, appending them to the stash.
 * Stops reading when a newline is found or EOF is reached.
 *
 * @param fd The file descriptor to read from.
 * @param stash The current stash string.
 * @return Updated stash with newly read data, or NULL on error.
 */
static char	*read_into_stash(int fd, char *stash)
{
	char	*buf;
	ssize_t	bytes_read;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	bytes_read = 1;
	while ((stash == NULL || !ft_strchr(stash, '\n')) && bytes_read != 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buf);
			free(stash);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		stash = gnl_strjoin(stash, buf);
		if (!stash)
			return (NULL);
	}
	free(buf);
	return (stash);
}

/**
 * @brief Reads the next line from a file descriptor.
 * 
 * Returns a newly allocated string containing the next line read from the
 * file descriptor @p fd, including the newline character if present.
 * Returns NULL on error or when there is nothing left to read.
 *
 * @param fd The file descriptor to read from.
 * @return A newly allocated string with the next line, or NULL if EOF or error.
 */
char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_into_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = clean_stash(stash);
	return (line);
}

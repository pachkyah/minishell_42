/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypachkou <ypachkou@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:18:11 by ypachkou          #+#    #+#             */
/*   Updated: 2026/01/11 01:35:38 by ypachkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdint.h>

// ---Character checks
int		ft_isalpha(int c); // Checks if character is alphabetic
int		ft_isdigit(int c); // Checks if character is a digit (0–9)
int		ft_isalnum(int c); // Checks if character is alphanumeric
int		ft_isascii(int c); // Checks if character is ASCII (0–127)
int		ft_isprint(int c); // Checks if character is printable

// ---String length
size_t	ft_strlen(const char *str);
	// Returns length of null-terminated string

// ---Memory operations
void	*ft_memset(void *b, int c, size_t len);
	// Fills memory with byte
void	ft_bzero(void *ptr, size_t n);
	// Sets memory to zero
void	*ft_memcpy(void *dest, const void *src, size_t n);
	// Copies memory (no overlap)
void	*ft_memmove(void *dest, const void *src, size_t n);
	// Safe memory copy with overlap
void	*ft_memchr(const void *s, int c, size_t n);
	// Search byte in memory
int		ft_memcmp(const void *s1, const void *s2, size_t n);
	// Compare memory areas

// ---String operations
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
	// Safe string copy
size_t	ft_strlcat(char *dest, const char *src, size_t size);
	// Safe string concat
char	*ft_strchr(const char *str, int c);
	// Find first occurrence of char
char	*ft_strrchr(const char *str, int c);
	// Find last occurrence of char
int		ft_strncmp(const char *s1, const char *s2, size_t n);
	// Compare strings up to n chars
char	*ft_strnstr(const char *hay, const char *needle, size_t len);
	// Locate substring

// ---Case conversion
int		ft_toupper(int c); // Converts to uppercase
int		ft_tolower(int c); // Converts to lowercase

// ---Conversions and allocation
int		ft_atoi(const char *str);
	// Convert ASCII string to int
char	*ft_itoa(int n);
	// Integer to ASCII string
void	*ft_calloc(size_t num, size_t size);
	// Allocates zero-initialized memory
char	*ft_strdup(const char *s);
	// Duplicates a string

// ---Output to file descriptor
void	ft_putchar_fd(char c, int fd);
	// Output char to fd
void	ft_putstr_fd(char *s, int fd);
	// Output string to fd
void	ft_putendl_fd(char *s, int fd);
	// Output string to fd with new line
void	ft_putnbr_fd(int n, int fd);
	// Output number to fd

// ---String manipulation
char	*ft_substr(char const *s, unsigned int start, size_t len);
	// Returns substring
char	*ft_strjoin(char const *s1, char const *s2);
	// Concatenate two strings
char	*ft_strtrim(char const *s1, char const *set);
	// Trim chars from start and end
char	**ft_split(char const *s, char c);
	// Split string by delimiter

// ---String iteration
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
	// Map function to each char (new string)
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
	// Apply function to each char in place

///---Bonus part---
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// ---Bonus functions for list operations
t_list	*ft_lstnew(void *content);
	// Create a new list element with given content
void	ft_lstadd_front(t_list **lst, t_list *new);
	// Add a new element at the beginning of the list
int		ft_lstsize(t_list *lst);
	// Count the number of elements in the list
t_list	*ft_lstlast(t_list *lst);
	// Return the last element of the list
void	ft_lstadd_back(t_list **lst, t_list *new);
	// Add a new element at the end of the list
void	ft_lstdelone(t_list *lst, void (*del)(void *));
	// Delete a single element using the provided delete function
void	ft_lstclear(t_list **lst, void (*del)(void *));
	// Delete and frees the entire list using the delete function
void	ft_lstiter(t_list *lst, void (*f)(void *));
	// Apply a function to each element's content in the list
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
	// Create a new list by applying a function to each element's content

///---Get next line part---
char	*get_next_line(int fd);
	// Gets the next line from a file

#endif
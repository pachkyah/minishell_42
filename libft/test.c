/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pachkyah <pachkyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 22:23:02 by pachkyah          #+#    #+#             */
/*   Updated: 2025/06/22 22:29:59 by pachkyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

// Helper for testing linked list
void print_list(t_list *lst)
{
	while (lst)
	{
		printf("Node: %s\n", (char *)lst->content);
		lst = lst->next;
	}
}

// Helper for lstmap
void *dup_content(void *content)
{
	return ft_strdup((char *)content);
}

void del_content(void *content)
{
	free(content);
}

// Helper for lstiter
void print_node_content(void *content)
{
	printf(" - %s\n", (char *)content);
}

// Helper for strmapi
char apply_toupper(unsigned int i, char c)
{
	(void)i;
	return ft_toupper(c);
}

// Helper for striteri
void apply_toupper_inplace(unsigned int i, char *c)
{
	(void)i;
	*c = ft_toupper(*c);
}

void test_char_and_string_functions()
{
	printf("==== Character & String Functions ====\n");
	printf("isalpha('A'): %d\n", ft_isalpha('A'));
	printf("isdigit('5'): %d\n", ft_isdigit('5'));
	printf("isalnum('9'): %d\n", ft_isalnum('9'));
	printf("isascii(127): %d\n", ft_isascii(127));
	printf("isprint(' '): %d\n", ft_isprint(' '));
	printf("strlen(\"Hello\"): %zu\n", ft_strlen("Hello"));

	char str1[20] = "World";
	char str2[] = "Hello ";
	ft_memset(str1, '*', 3);
	printf("memset: %s\n", str1);
	
	ft_bzero(str1, 3);
	printf("bzero: %s\n", str1);

	ft_memcpy(str1, str2, 5);
	printf("memcpy: %s\n", str1);

	ft_memmove(str1 + 2, str1, 5);
	printf("memmove overlap: %s\n", str1);

	char *chr = ft_memchr("abcdef", 'd', 6);
	printf("memchr: %s\n", chr);

	printf("memcmp: %d\n", ft_memcmp("abc", "abd", 3));

	char buffer1[20];
	ft_strlcpy(buffer1, "Copy", sizeof(buffer1));
	printf("strlcpy: %s\n", buffer1);

	char buffer2[20] = "Cat";
	ft_strlcat(buffer2, "Dog", sizeof(buffer2));
	printf("strlcat: %s\n", buffer2);

	printf("strchr: %s\n", ft_strchr("abcdef", 'd'));
	printf("strrchr: %s\n", ft_strrchr("abcabc", 'a'));
	printf("strncmp: %d\n", ft_strncmp("abc", "abd", 2));
	printf("strnstr: %s\n", ft_strnstr("foobar", "bar", 6));

	printf("toupper('a'): %d\n", ft_toupper('a'));
	printf("tolower('A'): %d\n", ft_tolower('A'));
}

void test_conversions_and_allocation()
{
	printf("\n==== Conversions & Allocation ====\n");
	printf("atoi(\"42\"): %d\n", ft_atoi("42"));

	char *itoa_test = ft_itoa(-123);
	printf("itoa(-123): %s\n", itoa_test);
	free(itoa_test);

	char *dup = ft_strdup("Hello");
	printf("strdup: %s\n", dup);
	free(dup);

	int *arr = (int *)ft_calloc(5, sizeof(int));
	printf("calloc: ");
	for (int i = 0; i < 5; i++) printf("%d ", arr[i]);
	printf("\n");
	free(arr);
}

void test_fd_functions()
{
	printf("\n==== Output to File Descriptor ====\n");
	ft_putchar_fd('X', 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("Hello fd\n", 1);
	ft_putnbr_fd(12345, 1);
	ft_putchar_fd('\n', 1);
}

void test_string_manipulation()
{
	printf("\n==== String Manipulation ====\n");

	char *sub = ft_substr("Hello World", 6, 5);
	printf("substr: %s\n", sub);
	free(sub);

	char *joined = ft_strjoin("Hello ", "Again");
	printf("strjoin: %s\n", joined);
	free(joined);

	char *trimmed = ft_strtrim("xxHello Worldxx", "x");
	printf("strtrim: %s\n", trimmed);
	free(trimmed);

	char **split = ft_split("A B C D", ' ');
	printf("split:\n");
	for (int i = 0; split[i]; i++) {
		printf("[%s]\n", split[i]);
		free(split[i]);
	}
	free(split);

	char *mapped = ft_strmapi("abc", apply_toupper);
    printf("strmapi: %s\n", mapped);
    free(mapped);

	char str[] = "xyz";
    ft_striteri(str, apply_toupper_inplace);
    printf("striteri: %s\n", str);
}

void test_linked_list()
{
	printf("\n==== Linked List ====\n");

	t_list *n1 = ft_lstnew(ft_strdup("one"));
	t_list *n2 = ft_lstnew(ft_strdup("two"));
	t_list *n3 = ft_lstnew(ft_strdup("three"));

	ft_lstadd_front(&n1, n2); // n2 -> n1
	ft_lstadd_back(&n2, n3);  // n2 -> n1 -> n3

	printf("List size: %d\n", ft_lstsize(n2));
	t_list *last = ft_lstlast(n2);
	printf("Last node: %s\n", (char *)last->content);

	printf("Iterate list:\n");
	ft_lstiter(n2, print_node_content);

	printf("Map list (duplicate content):\n");
	t_list *mapped = ft_lstmap(n2, dup_content, del_content);
	print_list(mapped);

	printf("Clear original list:\n");
	ft_lstclear(&n2, del_content);

	printf("Clear mapped list:\n");
	ft_lstclear(&mapped, del_content);
}

int main(void)
{
	test_char_and_string_functions();
	test_conversions_and_allocation();
	test_fd_functions();
	test_string_manipulation();
	test_linked_list();
	return (0);
}

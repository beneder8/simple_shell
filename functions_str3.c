#include "shell.h"

/**
 **_strncpy - copies a string
 *@first: the firstination string to be copied to
 *@last: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_str_copy(char *first, char *last, int n)
{
	int i, j;
	char *s = first;

	i = 0;
	while (last[i] != '\0' && i < n - 1)
	{
		first[i] = last[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			first[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@first: the first string
 *@last: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_str_concatenated(char *first, char *last, int n)
{
	int i, j;
	char *s = first;

	i = 0;
	j = 0;
	while (first[i] != '\0')
		i++;
	while (last[j] != '\0' && j < n)
	{
		first[i] = last[j];
		i++;
		j++;
	}
	if (j < n)
		first[i] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

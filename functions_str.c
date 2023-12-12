#include "shell.h"

/**
 * _showLem - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _showLem(char *s)
{
	int x = 0;

	if (!s)
		return (0);

	while (*s++)
		x++;
	return (x);
}

/**
 * _toCmp - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _toCmp(char *c1, char *c2)
{
	while (*c1 && *c2)
	{
		if (*c1 != *c2)
			return (*c1 - *c2);
		c1++;
		c2++;
	}
	if (*c1 == *c2)
		return (0);
	else
		return (*c1 < *c2 ? -1 : 1);
}

/**
 * starts_with - checks if x starts with starter
 * @starter: string to search
 * @x: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *starter, const char *x)
{
	while (*x)
		if (*x++ != *starter++)
			return (NULL);
	return ((char *)starter);
}

/**
 * _strcat - concatenates two strings
 * @one: the oneination buffer
 * @two: the source buffer
 *
 * Return: pointer to oneination buffer
 */
char *_strAdd(char *one, char *two)
{
	char *res = one;

	while (*one)
		one++;
	while (*two)
		*one++ = *two++;
	*one = *two;
	return (res);
}

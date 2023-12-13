#include "shell.h"

/**
 **_copynStr - copies a string
 *@destin: the destination string to be copied to
 *@source: the source string
 *@ncpy: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_copynStr(char *destin, char *source, int ncpy)
{
	int i, j;
	char *s = destin;

	i = 0;
	while (source[i] != '\0' && i < ncpy - 1)
	{
		destin[i] = source[i];
		i++;
	}
	if (i < ncpy)
	{
		j = i;
		while (j < ncpy)
		{
			destin[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_concnStr - concatenates two strings
 *@destin: the first string
 *@source: the second string
 *@ncpy: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_concnStr(char *destin, char *source, int ncpy)
{
	int i, j;
	char *s = destin;

	i = 0;
	j = 0;
	while (destin[i] != '\0')
		i++;
	while (source[j] != '\0' && j < ncpy)
	{
		destin[i] = source[j];
		i++;
		j++;
	}
	if (j < ncpy)
		destin[i] = '\0';
	return (s);
}

/**
 **_charStr - locates a character in a string
 *@s: the string to be parsed
 *@chr: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_charStr(char *s, char chr)
{
	do {
		if (*s == chr)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

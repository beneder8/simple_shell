#include "shell.h"

/**
 * _lengthStr - returns the length of a string
 * @slen: the string whose length to check
 *
 * Return: integer length of string
 */
int _lengthStr(char *slen)
{
	int i = 0;

	if (!slen)
		return (0);

	while (*slen++)
		i++;
	return (i);
}

/**
 * _compStr - performs lexicogarphic comparison of two strangs.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: negative if str1 < str2, positive if str1 > str2, zero if str1 == str2
 */
int _compStr(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * _startWith - checks if hello starts with world
 * @world: string to search
 * @hello: the substring to find
 *
 * Return: address of next char of world or NULL
 */
char *_startWith(const char *world, const char *hello)
{
	while (*hello)
		if (*hello++ != *world++)
			return (NULL);
	return ((char *)world);
}

/**
 * _concStr - concatenates two strings
 * @dstn: the destination buffer
 * @source: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_concStr(char *dstn, char *source)
{
	char *reslt = dstn;

	while (*dstn)
		dstn++;
	while (*source)
		*dstn++ = *source++;
	*dstn = *source;
	return (reslt);
}

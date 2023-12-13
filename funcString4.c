#include "shell.h"

/**
 * **_towordStr - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @del: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **_towordStr(char *str, char *del)
{
	int i, j, e, f, numwords = 0;
	char **x;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!_isDelimtr(str[i], del) && (_isDelimtr(str[i + 1], del) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	x = malloc((1 + numwords) * sizeof(char *));
	if (!x)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (_isDelimtr(str[i], del))
			i++;
		e = 0;
		while (!_isDelimtr(str[i + e], del) && str[i + e])
			e++;
		x[j] = malloc((e + 1) * sizeof(char));
		if (!x[j])
		{
			for (e = 0; e < j; e++)
				free(x[e]);
			free(x);
			return (NULL);
		}
		for (f = 0; f < e; f++)
			x[j][f] = str[i++];
		x[j][f] = 0;
	}
	x[j] = NULL;
	return (x);
}

/**
 * **_towordStr2 - splits a string into words
 * @str: the input string
 * @del: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **_towordStr2(char *str, char del)
{
	int i, j, e, f, numwords = 0;
	char **x;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != del && str[i + 1] == del) ||
		    (str[i] != del && !str[i + 1]) || str[i + 1] == del)
			numwords++;
	if (numwords == 0)
		return (NULL);
	x = malloc((1 + numwords) * sizeof(char *));
	if (!x)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == del && str[i] != del)
			i++;
		e = 0;
		while (str[i + e] != del && str[i + e] && str[i + e] != del)
			e++;
		x[j] = malloc((e + 1) * sizeof(char));
		if (!x[j])
		{
			for (e = 0; e < j; e++)
				free(x[e]);
			free(x);
			return (NULL);
		}
		for (f = 0; f < e; f++)
			x[j][f] = str[i++];
		x[j][f] = 0;
	}
	x[j] = NULL;
	return (x);
}

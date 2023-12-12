#include "shell.h"

/**
 * _strcpy - copies a string
 * @one: the oneination
 * @two: the source
 *
 * Return: pointer to oneination
 */
char *_strmul(char *one, char *two)
{
	int i = 0;

	if (one == two || two == 0)
		return (one);
	while (two[i])
	{
		one[i] = two[i];
		i++;
	}
	one[i] = 0;
	return (one);
}

/**
 * _strdup - duplicates a string
 * @s: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_str_duplicat(const char *s)
{
	int len = 0;
	char *s;

	if (s == NULL)
		return (NULL);
	while (*s++)
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--s;
	return (ret);
}

/**
 *_puts - prints an input string
 *@s: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		_putchar(s[i]);
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

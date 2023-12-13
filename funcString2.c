#include "shell.h"

/**
 * _copyStr - copies a string
 * @dstn: the destination
 * @source: the source
 *
 * Return: pointer to destination
 */
char *_copyStr(char *dstn, char *source)
{
	int i = 0;

	if (dstn == source || source == 0)
		return (dstn);
	while (source[i])
	{
		dstn[i] = source[i];
		i++;
	}
	dstn[i] = 0;
	return (dstn);
}

/**
 * _duplictStr - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_duplictStr(const char *str)
{
	int length = 0;
	char *reslt;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	reslt = malloc(sizeof(char) * (length + 1));
	if (!reslt)
		return (NULL);
	for (length++; length--;)
		reslt[length] = *--str;
	return (reslt);
}

/**
 *_putStr - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void _putStr(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putChar(str[i]);
		i++;
	}
}

/**
 * _putChar - writes the character p to stdout
 * @p: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putChar(char p)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (p == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (p != BUF_FLUSH)
		buf[i++] = p;
	return (1);
}

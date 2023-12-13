#include "shell.h"

/**
 *_printErrorStr - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _printErrorStr(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_printErrorChar(str[i]);
		i++;
	}
}

/**
 * _printErrorChar - writes the character r to stderr
 * @r: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _printErrorChar(char r)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (r == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (r != BUF_FLUSH)
		buf[i++] = r;
	return (1);
}

/**
 * _writeCharToFD - writes the character r to given file descriptor
 * @r: The character to print
 * @filedsc: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _writeCharToFD(char r, int filedsc)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (r == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(filedsc, buf, i);
		i = 0;
	}
	if (r != BUF_FLUSH)
		buf[i++] = r;
	return (1);
}

/**
 *_printStrToFD - prints an input string to a given file descriptor
 * @str: the string to be printed
 * @filedsc: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _printStrToFD(char *str, int filedsc)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _writeCharToFD(*str++, filedsc);
	}
	return (i);
}

#include "shell.h"

/**
 * _strToInt2 - converts a string to an integer
 * @stocnv: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _strToInt2(char *stocnv)
{
	int i = 0;
	unsigned long int result = 0;

	if (*stocnv == '+')
		stocnv++;  /* TODO: why does this make main return 255? */
	for (i = 0;  stocnv[i] != '\0'; i++)
	{
		if (stocnv[i] >= '0' && stocnv[i] <= '9')
		{
			result *= 10;
			result += (stocnv[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * _prntError - prints an error message
 * @shellInfo: the parameter & return shellInfo struct
 * @strerr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void _prntError(info_t *shellInfo, char *strerr)
{
	_printErrorStr(shellInfo->fname);
	_printErrorStr(": ");
	_prntDec(shellInfo->line_count, STDERR_FILENO);
	_printErrorStr(": ");
	_printErrorStr(shellInfo->argv[0]);
	_printErrorStr(": ");
	_printErrorStr(strerr);
}

/**
 * _prntDec - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int _prntDec(int input, int fd)
{
	int (*__putChar)(char) = _putChar;
	int i, count = 0;
	unsigned int a, current;

	if (fd == STDERR_FILENO)
		__putChar = _printErrorChar;
	if (input < 0)
	{
		a = -input;
		__putChar('-');
		count++;
	}
	else
		a = input;
	current = a;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (a / i)
		{
			__putChar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putChar('0' + current);
	count++;

	return (count);
}

/**
 * _cnvrtNmbr - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @argflags: argument flags
 *
 * Return: string
 */
char *_cnvrtNmbr(long int num, int base, int argflags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *p;
	unsigned long n = num;

	if (!(argflags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = argflags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buffer[49];
	*p = '\0';

	do	{
		*--p = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--p = sign;
	return (p);
}

/**
 * _remvCmnts - function replaces first instance of '#' with '\0'
 * @bffr: address of the string to modify
 *
 * Return: Always 0;
 */
void _remvCmnts(char *bffr)
{
	int i;

	for (i = 0; bffr[i] != '\0'; i++)
		if (bffr[i] == '#' && (!i || bffr[i - 1] == ' '))
		{
			bffr[i] = '\0';
			break;
		}
}

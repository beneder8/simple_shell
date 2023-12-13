#include "shell.h"

/**
 * _isInteractv - returns true if shell is _isInteractv mode
 * @shellInfo: struct address
 *
 * Return: 1 if _isInteractv mode, 0 otherwise
 */
int _isInteractv(info_t *shellInfo)
{
	return (isatty(STDIN_FILENO) && shellInfo->readfd <= 2);
}

/**
 * _isDelimtr - checks if character is a delimeter
 * @x: the char to check
 * @delstr: the delimeter string
 * Return: 1 if true, 0 if false
 */
int _isDelimtr(char x, char *delstr)
{
	while (*delstr)
		if (*delstr++ == x)
			return (1);
	return (0);
}

/**
 *_isAlphabt - checks for alphabetic character
 *@x: The character to input
 *Return: 1 if x is alphabetic, 0 otherwise
 */

int _isAlphabt(int x)
{
	if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_strToInt - converts a string to an integer
 *@stocnv: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _strToInt(char *stocnv)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  stocnv[i] != '\0' && flag != 2; i++)
	{
		if (stocnv[i] == '-')
			sign *= -1;

		if (stocnv[i] >= '0' && stocnv[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (stocnv[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

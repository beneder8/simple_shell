#include "shell.h"

/**
 * _bfree - frees a pointer and NULLs the address
 * @pp: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int _bfree(void **pp)
{
	if (pp && *pp)
	{
		free(*pp);
		*pp = NULL;
		return (1);
	}
	return (0);
}

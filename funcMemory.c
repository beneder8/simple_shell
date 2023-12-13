#include "shell.h"

/**
 **_setMemory - fills memory with a constant byte
 *@x: the pointer to the memory area
 *@y: the byte to fill *x with
 *@z: the amount of bytes to be filled
 *Return: (x) a pointer to the memory area x
 */
char *_setMemory(char *x, char y, unsigned int z)
{
	unsigned int i;

	for (i = 0; i < z; i++)
		x[i] = y;
	return (x);
}

/**
 * _freeStr - frees a string of strings
 * @sos: string of strings
 */
void _freeStr(char **sos)
{
	char **d = sos;

	if (!sos)
		return;
	while (*sos)
		free(*sos++);
	free(d);
}

/**
 * _reallocMem - reallocates a block of memory
 * @pp: pointer to previous malloc'ated block
 * @oldsz: byte size of previous block
 * @newsz: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_reallocMem(void *pp, unsigned int oldsz, unsigned int newsz)
{
	char *p;

	if (!pp)
		return (malloc(newsz));
	if (!newsz)
		return (free(pp), NULL);
	if (newsz == oldsz)
		return (pp);

	p = malloc(newsz);
	if (!p)
		return (NULL);

	oldsz = oldsz < newsz ? oldsz : newsz;
	while (oldsz--)
		p[oldsz] = ((char *)pp)[oldsz];
	free(pp);
	return (p);
}

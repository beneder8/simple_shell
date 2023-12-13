#include "shell.h"

/**
 * _lenghtList - determines length of linked list
 * @fnode: pointer to first node
 *
 * Return: size of list
 */
size_t _lenghtList(const list_t *fnode)
{
	size_t i = 0;

	while (fnode)
	{
		fnode = fnode->next;
		i++;
	}
	return (i);
}

/**
 * _listToStr - returns an array of strings of the list->str
 * @h: pointer to first node
 *
 * Return: array of strings
 */
char **_listToStr(list_t *h)
{
	list_t *node = h;
	size_t i = _lenghtList(h), j;
	char **s;
	char *str;

	if (!h || !i)
		return (NULL);
	s = malloc(sizeof(char *) * (i + 1));
	if (!s)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_lengthStr(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(s[j]);
			free(s);
			return (NULL);
		}

		str = _copyStr(str, node->str);
		s[i] = str;
	}
	s[i] = NULL;
	return (s);
}


/**
 * _prntList - prints all elements of a list_t linked list
 * @fnode: pointer to first node
 *
 * Return: size of list
 */
size_t _prntList(const list_t *fnode)
{
	size_t i = 0;

	while (fnode)
	{
		_putStr(_cnvrtNmbr(fnode->num, 10, 0));
		_putChar(':');
		_putChar(' ');
		_putStr(fnode->str ? fnode->str : "(nil)");
		_putStr("\n");
		fnode = fnode->next;
		i++;
	}
	return (i);
}

/**
 * _nodeStartWith - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @x: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *_nodeStartWith(list_t *node, char *prefix, char x)
{
	char *f = NULL;

	while (node)
	{
		f = _startWith(node->str, prefix);
		if (f && ((x == -1) || (*f == x)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * _getNodeIndex - gets the index of a node
 * @h: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t _getNodeIndex(list_t *h, list_t *node)
{
	size_t i = 0;

	while (h)
	{
		if (h == node)
			return (i);
		h = h->next;
		i++;
	}
	return (-1);
}

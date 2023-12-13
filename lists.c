#include "shell.h"

/**
 * _nodeStart - adds a node to the start of the list
 * @hdnode: address of pointer to head node
 * @str: str field of node
 * @nmbr: node index used by history
 *
 * Return: size of list
 */
list_t *_nodeStart(list_t **hdnode, const char *str, int nmbr)
{
	list_t *newhd;

	if (!hdnode)
		return (NULL);
	newhd = malloc(sizeof(list_t));
	if (!newhd)
		return (NULL);
	_setMemory((void *)newhd, 0, sizeof(list_t));
	newhd->nmbr = nmbr;
	if (str)
	{
		newhd->str = _duplictStr(str);
		if (!newhd->str)
		{
			free(newhd);
			return (NULL);
		}
	}
	newhd->next = *hdnode;
	*hdnode = newhd;
	return (newhd);
}

/**
 * _nodeEnd - adds a node to the end of the list
 * @hdnode: address of pointer to head node
 * @str: str field of node
 * @nmbr: node index used by history
 *
 * Return: size of list
 */
list_t *_nodeEnd(list_t **hdnode, const char *str, int nmbr)
{
	list_t *newnd, *node;

	if (!hdnode)
		return (NULL);

	node = *hdnode;
	newnd = malloc(sizeof(list_t));
	if (!newnd)
		return (NULL);
	_setMemory((void *)newnd, 0, sizeof(list_t));
	newnd->nmbr = nmbr;
	if (str)
	{
		newnd->str = _duplictStr(str);
		if (!newnd->str)
		{
			free(newnd);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = newnd;
	}
	else
		*hdnode = newnd;
	return (newnd);
}

/**
 * _prntListStr - prints only the str element of a list_t linked list
 * @fnode: pointer to first node
 *
 * Return: size of list
 */
size_t _prntListStr(const list_t *fnode)
{
	size_t i = 0;

	while (fnode)
	{
		_putStr(fnode->str ? fnode->str : "(nil)");
		_putStr("\n");
		fnode = fnode->next;
		i++;
	}
	return (i);
}

/**
 * _delNodeIndex - deletes node at given index
 * @hdnode: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int _delNodeIndex(list_t **hdnode, unsigned int index)
{
	list_t *node, *prevnd;
	unsigned int i = 0;

	if (!hdnode || !*hdnode)
		return (0);

	if (!index)
	{
		node = *hdnode;
		*hdnode = (*hdnode)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *hdnode;
	while (node)
	{
		if (i == index)
		{
			prevnd->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prevnd = node;
		node = node->next;
	}
	return (0);
}

/**
 * _freeList - frees all nodes of a list
 * @pthead: address of pointer to head node
 *
 * Return: void
 */
void _freeList(list_t **pthead)
{
	list_t *node, *nextnd, *hdnode;

	if (!pthead || !*pthead)
		return;
	hdnode = *pthead;
	node = hdnode;
	while (node)
	{
		nextnd = node->next;
		free(node->str);
		free(node);
		node = nextnd;
	}
	*pthead = NULL;
}

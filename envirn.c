#include "shell.h"

/**
 * _thisEnvirn - prints the current environment
 * @shellInfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _thisEnvirn(info_t *shellInfo)
{
	_prntListStr(shellInfo->env);
	return (0);
}

/**
 * _getEnvirn - gets the value of an environment variable
 * @shellInfo: Structure containing potential arguments. Used to maintain
 * @envname: environment var name
 *
 * Return: the value
 */
char *_getEnvirn(info_t *shellInfo, const char *envname)
{
	list_t *node = shellInfo->env;
	char *j;

	while (node)
	{
		j = _startWith(node->str, envname);
		if (j && *j)
			return (j);
		node = node->next;
	}
	return (NULL);
}

/**
 * _setEnvirn - Initialize a new environment variable,
 *             or modify an existing one
 * @shellInfo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _setEnvirn(info_t *shellInfo)
{
	if (shellInfo->argc != 3)
	{
		_printErrorStr("Incorrect number of arguements\n");
		return (1);
	}
	if (_setEnvr(shellInfo, shellInfo->argv[1], shellInfo->argv[2]))
		return (0);
	return (1);
}

/**
 * _unSetEnvirn - Remove an environment variable
 * @shellInfo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _unSetEnvirn(info_t *shellInfo)
{
	int i;

	if (shellInfo->argc == 1)
	{
		_printErrorStr("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= shellInfo->argc; i++)
		_unsetEnvr(shellInfo, shellInfo->argv[i]);

	return (0);
}

/**
 * _pptEnvList - populates environment linked list
 * @shellInfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _pptEnvList(info_t *shellInfo)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		_nodeEnd(&node, environ[i], 0);
	shellInfo->env = node;
	return (0);
}

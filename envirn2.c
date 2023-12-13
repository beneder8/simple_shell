#include "shell.h"

/**
 * _getEnviron - returns the string array copy of our environ
 * @shellInfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **_getEnviron(info_t *shellInfo)
{
	if (!shellInfo->environ || shellInfo->env_changed)
	{
		shellInfo->environ = _listToStr(shellInfo->env);
		shellInfo->env_changed = 0;
	}

	return (shellInfo->environ);
}

/**
 * _unsetEnvr - Remove an environment variable
 * @shellInfo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @varp: the string env var property
 */
int _unsetEnvr(info_t *shellInfo, char *varp)
{
	list_t *node = shellInfo->env;
	size_t i = 0;
	char *j;

	if (!node || !varp)
		return (0);

	while (node)
	{
		j = _startWith(node->str, varp);
		if (j && *j == '=')
		{
			shellInfo->env_changed = _delNodeIndex(&(shellInfo->env), i);
			i = 0;
			node = shellInfo->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (shellInfo->env_changed);
}

/**
 * _setEnvr - Initialize a new environment variable,
 *             or modify an existing one
 * @shellInfo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @varp: the string env var property
 * @varv: the string env var value
 *  Return: Always 0
 */
int _setEnvr(info_t *shellInfo, char *varp, char *varv)
{
	char *bffr = NULL;
	list_t *node;
	char *j;

	if (!varp || !varv)
		return (0);

	bffr = malloc(_lengthStr(varp) + _lengthStr(varv) + 2);
	if (!bffr)
		return (1);
	_copyStr(bffr, varp);
	_concStr(bffr, "=");
	_concStr(bffr, varv);
	node = shellInfo->env;
	while (node)
	{
		j = _startWith(node->str, varp);
		if (j && *j == '=')
		{
			free(node->str);
			node->str = bffr;
			shellInfo->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	_nodeEnd(&(shellInfo->env), bffr, 0);
	free(bffr);
	shellInfo->env_changed = 1;
	return (0);
}

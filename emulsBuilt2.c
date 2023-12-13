#include "shell.h"

/**
 * _dispHistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @shellInfo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _dispHistory(info_t *shellInfo)
{
	_prntList(shellInfo->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @shellInfo: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *shellInfo, char *str)
{
	char *j, s;
	int rslt;

	j = _charStr(str, '=');
	if (!j)
		return (1);
	s = *j;
	*j = 0;
	rslt = _delNodeIndex(&(shellInfo->alias),
		_getNodeIndex(shellInfo->alias, _nodeStartWith(shellInfo->alias, str, -1)));
	*j = s;
	return (rslt);
}

/**
 * set_alias - sets alias to string
 * @shellInfo: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *shellInfo, char *str)
{
	char *j;

	j = _charStr(str, '=');
	if (!j)
		return (1);
	if (!*++j)
		return (unset_alias(shellInfo, str));

	unset_alias(shellInfo, str);
	return (_nodeEnd(&(shellInfo->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @aliasnd: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *aliasnd)
{
	char *j = NULL, *a = NULL;

	if (aliasnd)
	{
		j = _charStr(aliasnd->str, '=');
		for (a = aliasnd->str; a <= j; a++)
			_putChar(*a);
		_putChar('\'');
		_putStr(j + 1);
		_putStr("'\n");
		return (0);
	}
	return (1);
}

/**
 * _mAlias - mimics the alias builtin (man alias)
 * @shellInfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _mAlias(info_t *shellInfo)
{
	int i = 0;
	char *j = NULL;
	list_t *aliasnd = NULL;

	if (shellInfo->argc == 1)
	{
		aliasnd = shellInfo->alias;
		while (aliasnd)
		{
			print_alias(aliasnd);
			aliasnd = aliasnd->next;
		}
		return (0);
	}
	for (i = 1; shellInfo->argv[i]; i++)
	{
		j = _charStr(shellInfo->argv[i], '=');
		if (j)
			set_alias(shellInfo, shellInfo->argv[i]);
		else
			print_alias(_nodeStartWith(shellInfo->alias, shellInfo->argv[i], '='));
	}

	return (0);
}

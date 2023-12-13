#include "shell.h"

/**
 * _isChainDelm - test if current char in buffer is a chain delimeter
 * @shellInfo: the parameter struct
 * @bffr: the char buffer
 * @pos: address of current position in buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int _isChainDelm(info_t *shellInfo, char *bffr, size_t *pos)
{
	size_t j = *pos;

	if (bffr[j] == '|' && bffr[j + 1] == '|')
	{
		bffr[j] = 0;
		j++;
		shellInfo->cmd_buf_type = CMD_OR;
	}
	else if (bffr[j] == '&' && bffr[j + 1] == '&')
	{
		bffr[j] = 0;
		j++;
		shellInfo->cmd_buf_type = CMD_AND;
	}
	else if (bffr[j] == ';') /* found end of this command */
	{
		bffr[j] = 0; /* replace semicolon with null */
		shellInfo->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pos = j;
	return (1);
}

/**
 * _checkChain - checks we should continue chaining based on last status
 * @shellInfo: the parameter struct
 * @bffr: the char buffer
 * @pos: address of current position in buffer
 * @i: starting position in buffer
 * @length: length of buffer
 *
 * Return: Void
 */
void _checkChain(info_t *shellInfo, char *bffr, size_t *pos, size_t i, size_t length)
{
	size_t j = *pos;

	if (shellInfo->cmd_buf_type == CMD_AND)
	{
		if (shellInfo->status)
		{
			bffr[i] = 0;
			j = length;
		}
	}
	if (shellInfo->cmd_buf_type == CMD_OR)
	{
		if (!shellInfo->status)
		{
			bffr[i] = 0;
			j = length;
		}
	}

	*pos = j;
}

/**
 * _replaceAlias - replaces an aliases in the tokenized string
 * @shellInfo: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _replaceAlias(info_t *shellInfo)
{
	int i;
	list_t *node;
	char *pos;

	for (i = 0; i < 10; i++)
	{
		node = _nodeStartWith(shellInfo->alias, shellInfo->argv[0], '=');
		if (!node)
			return (0);
		free(shellInfo->argv[0]);
		pos = _charStr(node->str, '=');
		if (!pos)
			return (0);
		pos = _duplictStr(pos + 1);
		if (!pos)
			return (0);
		shellInfo->argv[0] = pos;
	}
	return (1);
}

/**
 * _replaceVar - replaces vars in the tokenized string
 * @shellInfo: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _replaceVar(info_t *shellInfo)
{
	int i = 0;
	list_t *node;

	for (i = 0; shellInfo->argv[i]; i++)
	{
		if (shellInfo->argv[i][0] != '$' || !shellInfo->argv[i][1])
			continue;

		if (!_compStr(shellInfo->argv[i], "$?"))
		{
			_replaceStr(&(shellInfo->argv[i]),
				_duplictStr(_cnvrtNmbr(shellInfo->status, 10, 0)));
			continue;
		}
		if (!_compStr(shellInfo->argv[i], "$$"))
		{
			_replaceStr(&(shellInfo->argv[i]),
				_duplictStr(_cnvrtNmbr(getpid(), 10, 0)));
			continue;
		}
		node = _nodeStartWith(shellInfo->env, &shellInfo->argv[i][1], '=');
		if (node)
		{
			_replaceStr(&(shellInfo->argv[i]),
				_duplictStr(_charStr(node->str, '=') + 1));
			continue;
		}
		_replaceStr(&shellInfo->argv[i], _duplictStr(""));

	}
	return (0);
}

/**
 * _replaceStr - replaces string
 * @oldstr: address of old string
 * @newstr: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _replaceStr(char **oldstr, char *newstr)
{
	free(*oldstr);
	*oldstr = newstr;
	return (1);
}

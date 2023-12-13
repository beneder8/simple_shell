#include "shell.h"

/**
 * _clearInfo - initializes info_t struct
 * @shellInfo: struct address
 */
void _clearInfo(info_t *shellInfo)
{
	shellInfo->arg = NULL;
	shellInfo->argv = NULL;
	shellInfo->path = NULL;
	shellInfo->argc = 0;
}

/**
 * _setInfo - initializes info_t struct
 * @shellInfo: struct address
 * @argvectr: argument vector
 */
void _setInfo(info_t *shellInfo, char **argvectr)
{
	int i = 0;

	shellInfo->fname = argvectr[0];
	if (shellInfo->arg)
	{
		shellInfo->argv = _towordStr(shellInfo->arg, " \t");
		if (!shellInfo->argv)
		{

			shellInfo->argv = malloc(sizeof(char *) * 2);
			if (shellInfo->argv)
			{
				shellInfo->argv[0] = _duplictStr(shellInfo->arg);
				shellInfo->argv[1] = NULL;
			}
		}
		for (i = 0; shellInfo->argv && shellInfo->argv[i]; i++)
			;
		shellInfo->argc = i;

		_replaceAlias(shellInfo);
		_replaceVar(shellInfo);
	}
}

/**
 * _freeInfo - frees info_t struct fields
 * @shellInfo: struct address
 * @flds: true if freeing all fields
 */
void _freeInfo(info_t *shellInfo, int flds)
{
	_freeStr(shellInfo->argv);
	shellInfo->argv = NULL;
	shellInfo->path = NULL;
	if (flds)
	{
		if (!shellInfo->cmd_buf)
			free(shellInfo->arg);
		if (shellInfo->env)
			_freeList(&(shellInfo->env));
		if (shellInfo->history)
			_freeList(&(shellInfo->history));
		if (shellInfo->alias)
			_freeList(&(shellInfo->alias));
		_freeStr(shellInfo->environ);
			shellInfo->environ = NULL;
		_bfree((void **)shellInfo->cmd_buf);
		if (shellInfo->readfd > 2)
			close(shellInfo->readfd);
		_putChar(BUF_FLUSH);
	}
}

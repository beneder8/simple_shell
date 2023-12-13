#include "shell.h"

/**
 * _shellLoop - main shell loop
 * @shellInfo: the parameter & return shellInfo struct
 * @agrvctr: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int _shellLoop(info_t *shellInfo, char **agrvctr)
{
	ssize_t s = 0;
	int br = 0;

	while (s != -1 && br != -2)
	{
		_clearInfo(shellInfo);
		if (_isInteractv(shellInfo))
			_putStr("$ ");
		_printErrorChar(BUF_FLUSH);
		s = _getInput(shellInfo);
		if (s != -1)
		{
			_setInfo(shellInfo, agrvctr);
			br = _findBuiltin(shellInfo);
			if (br == -1)
				_findCommand(shellInfo);
		}
		else if (_isInteractv(shellInfo))
			_putChar('\n');
		_freeInfo(shellInfo, 0);
	}
	_writeHist(shellInfo);
	_freeInfo(shellInfo, 1);
	if (!_isInteractv(shellInfo) && shellInfo->status)
		exit(shellInfo->status);
	if (br == -2)
	{
		if (shellInfo->err_num == -1)
			exit(shellInfo->status);
		exit(shellInfo->err_num);
	}
	return (br);
}

/**
 * _findBuiltin - finds a builtin command
 * @shellInfo: the parameter & return shellInfo struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int _findBuiltin(info_t *shellInfo)
{
	int i, binr = -1;
	builtin_table builtintbl[] = {
		{"exit", _exitShell},
		{"env", _thisEnvirn},
		{"help", _showHelp},
		{"history", _dispHistory},
		{"setenv", _setEnvirn},
		{"unsetenv", _unSetEnvirn},
		{"cd", _changeDirectory},
		{"alias", _mAlias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_compStr(shellInfo->argv[0], builtintbl[i].type) == 0)
		{
			shellInfo->line_count++;
			binr = builtintbl[i].func(shellInfo);
			break;
		}
	return (binr);
}

/**
 * _findCommand - finds a command in PATH
 * @shellInfo: the parameter & return shellInfo struct
 *
 * Return: void
 */
void _findCommand(info_t *shellInfo)
{
	char *path = NULL;
	int i, j;

	shellInfo->path = shellInfo->argv[0];
	if (shellInfo->linecount_flag == 1)
	{
		shellInfo->line_count++;
		shellInfo->linecount_flag = 0;
	}
	for (i = 0, j = 0; shellInfo->arg[i]; i++)
		if (!_isDelimtr(shellInfo->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	path = _fndPath(shellInfo, _getEnvirn(shellInfo, "PATH="), shellInfo->argv[0]);
	if (path)
	{
		shellInfo->path = path;
		_forkCommand(shellInfo);
	}
	else
	{
		if ((_isInteractv(shellInfo) || _getEnvirn(shellInfo, "PATH=")
			|| shellInfo->argv[0][0] == '/') && _execuCommand(shellInfo, shellInfo->argv[0]))
			_forkCommand(shellInfo);
		else if (*(shellInfo->arg) != '\n')
		{
			shellInfo->status = 127;
			_prntError(shellInfo, "not found\n");
		}
	}
}

/**
 * _forkCommand - forks a an exec thread to run cmd
 * @shellInfo: the parameter & return shellInfo struct
 *
 * Return: void
 */
void _forkCommand(info_t *shellInfo)
{
	pid_t childpd;

	childpd = fork();
	if (childpd == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (childpd == 0)
	{
		if (execve(shellInfo->path, shellInfo->argv, _getEnviron(shellInfo)) == -1)
		{
			_freeInfo(shellInfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(shellInfo->status));
		if (WIFEXITED(shellInfo->status))
		{
			shellInfo->status = WEXITSTATUS(shellInfo->status);
			if (shellInfo->status == 126)
				_prntError(shellInfo, "Permission denied\n");
		}
	}
}

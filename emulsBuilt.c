#include "shell.h"

/**
 * _exitShell - exits the shell
 * @shellInfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if shellInfo.argv[0] != "exit"
 */
int _exitShell(info_t *shellInfo)
{
	int _exCheck;

	if (shellInfo->argv[1])  /* If there is an exit arguement */
	{
		_exCheck = _strToInt2(shellInfo->argv[1]);
		if (_exCheck == -1)
		{
			shellInfo->status = 2;
			_prntError(shellInfo, "Illegal number: ");
			_printErrorStr(shellInfo->argv[1]);
			_printErrorChar('\n');
			return (1);
		}
		shellInfo->err_num = _strToInt2(shellInfo->argv[1]);
		return (-2);
	}
	shellInfo->err_num = -1;
	return (-2);
}

/**
 * _changeDirectory - changes the current directory of the process
 * @shellInfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _changeDirectory(info_t *shellInfo)
{
	char *i, *dir, buffer[1024];
	int j;

	i = getcwd(buffer, 1024);
	if (!i)
		_putStr("TODO: >>getcwd failure emsg here<<\n");
	if (!shellInfo->argv[1])
	{
		dir = _getEnvirn(shellInfo, "HOME=");
		if (!dir)
			j = /* TODO: what should this be? */
				chdir((dir = _getEnvirn(shellInfo, "PWD=")) ? dir : "/");
		else
			j = chdir(dir);
	}
	else if (_compStr(shellInfo->argv[1], "-") == 0)
	{
		if (!_getEnvirn(shellInfo, "OLDPWD="))
		{
			_putStr(i);
			_putChar('\n');
			return (1);
		}
		_putStr(_getEnvirn(shellInfo, "OLDPWD=")), _putChar('\n');
		j = /* TODO: what should this be? */
			chdir((dir = _getEnvirn(shellInfo, "OLDPWD=")) ? dir : "/");
	}
	else
		j = chdir(shellInfo->argv[1]);
	if (j == -1)
	{
		_prntError(shellInfo, "can't cd to ");
		_printErrorStr(shellInfo->argv[1]), _printErrorChar('\n');
	}
	else
	{
		_setEnvr(shellInfo, "OLDPWD", _getEnvirn(shellInfo, "PWD="));
		_setEnvr(shellInfo, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _showHelp - displays help information for the shell
 * @shellInfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _showHelp(info_t *shellInfo)
{
	char **argarr;

	argarr = shellInfo->argv;
	_putStr("help call works. Function not yet implemented \n");
	if (0)
		_putStr(*argarr); /* temp att_unused workaround */
	return (0);
}

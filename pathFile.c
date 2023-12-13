#include "shell.h"

/**
 * _execuCommand - determines if a file is an executable command
 * @shellInfo: the shellInfo struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int _execuCommand(info_t *shellInfo, char *path)
{
	struct stat st;

	(void)shellInfo;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * _dupCharacters - duplicates characters
 * @pthstr: the PATH string
 * @startindx: starting index
 * @stopindx: stopping index
 *
 * Return: pointer to new buffer
 */
char *_dupCharacters(char *pthstr, int startindx, int stopindx)
{
	static char bffr[1024];
	int i = 0, j = 0;

	for (j = 0, i = startindx; i < stopindx; i++)
		if (pthstr[i] != ':')
			bffr[j++] = pthstr[i];
	bffr[j] = 0;
	return (bffr);
}

/**
 * _fndPath - finds this cmd in the PATH string
 * @shellInfo: the shellInfo struct
 * @pthstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *_fndPath(info_t *shellInfo, char *pthstr, char *cmd)
{
	int i = 0, crrpos = 0;
	char *path;

	if (!pthstr)
		return (NULL);
	if ((_lengthStr(cmd) > 2) && _startWith(cmd, "./"))
	{
		if (_execuCommand(shellInfo, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pthstr[i] || pthstr[i] == ':')
		{
			path = _dupCharacters(pthstr, crrpos, i);
			if (!*path)
				_concStr(path, cmd);
			else
			{
				_concStr(path, "/");
				_concStr(path, cmd);
			}
			if (_execuCommand(shellInfo, path))
				return (path);
			if (!pthstr[i])
				break;
			crrpos = i;
		}
		i++;
	}
	return (NULL);
}

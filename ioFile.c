#include "shell.h"

/**
 * _getHistFile - gets the history file
 * @shellInfo: parameter struct
 *
 * Return: allocated string containg history file
 */

char *_getHistFile(info_t *shellInfo)
{
	char *bffr, *dir;

	dir = _getEnvirn(shellInfo, "HOME=");
	if (!dir)
		return (NULL);
	bffr = malloc(sizeof(char) * (_lengthStr(dir) + _lengthStr(HIST_FILE) + 2));
	if (!bffr)
		return (NULL);
	bffr[0] = 0;
	_copyStr(bffr, dir);
	_concStr(bffr, "/");
	_concStr(bffr, HIST_FILE);
	return (bffr);
}

/**
 * _writeHist - creates a file, or appends to an existing file
 * @shellInfo: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int _writeHist(info_t *shellInfo)
{
	ssize_t j;
	char *f = _getHistFile(shellInfo);
	list_t *node = NULL;

	if (!f)
		return (-1);

	j = open(f, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(f);
	if (j == -1)
		return (-1);
	for (node = shellInfo->history; node; node = node->next)
	{
		_printStrToFD(node->str, j);
		_writeCharToFD('\n', j);
	}
	_writeCharToFD(BUF_FLUSH, j);
	close(j);
	return (1);
}

/**
 * _readHist - reads history from file
 * @shellInfo: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int _readHist(info_t *shellInfo)
{
	int i, last = 0, linecnt = 0;
	ssize_t j, rdlen, fsize = 0;
	struct stat st;
	char *bffr = NULL, *f = _getHistFile(shellInfo);

	if (!f)
		return (0);

	j = open(f, O_RDONLY);
	free(f);
	if (j == -1)
		return (0);
	if (!fstat(j, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	bffr = malloc(sizeof(char) * (fsize + 1));
	if (!bffr)
		return (0);
	rdlen = read(j, bffr, fsize);
	bffr[fsize] = 0;
	if (rdlen <= 0)
		return (free(bffr), 0);
	close(j);
	for (i = 0; i < fsize; i++)
		if (bffr[i] == '\n')
		{
			bffr[i] = 0;
			_buildHistList(shellInfo, bffr + last, linecnt++);
			last = i + 1;
		}
	if (last != i)
		_buildHistList(shellInfo, bffr + last, linecnt++);
	free(bffr);
	shellInfo->histcount = linecnt;
	while (shellInfo->histcount-- >= HIST_MAX)
		_delNodeIndex(&(shellInfo->history), 0);
	_renmbrHist(shellInfo);
	return (shellInfo->histcount);
}

/**
 * _buildHistList - adds entry to a history linked list
 * @shellInfo: Structure containing potential arguments. Used to maintain
 * @bffr: buffer
 * @linecnt: the history linecnt, histcount
 *
 * Return: Always 0
 */
int _buildHistList(info_t *shellInfo, char *bffr, int linecnt)
{
	list_t *node = NULL;

	if (shellInfo->history)
		node = shellInfo->history;
	_nodeEnd(&node, bffr, linecnt);

	if (!shellInfo->history)
		shellInfo->history = node;
	return (0);
}

/**
 * _renmbrHist - renumbers the history linked list after changes
 * @shellInfo: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int _renmbrHist(info_t *shellInfo)
{
	list_t *node = shellInfo->history;
	int i = 0;

	while (node)
	{
		node->nmbr = i++;
		node = node->next;
	}
	return (shellInfo->histcount = i);
}

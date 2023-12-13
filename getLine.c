#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @shellInfo: parameter struct
 * @bffr: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *shellInfo, char **bffr, size_t *len)
{
	ssize_t rlt = 0;
	size_t lenp = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*_bfree((void **)shellInfo->cmd_buf);*/
		free(*bffr);
		*bffr = NULL;
		signal(SIGINT, _sgntHndler);
#if USE_GETLINE
		rlt = getline(bffr, &lenp, stdin);
#else
		rlt = _getLine(shellInfo, bffr, &lenp);
#endif
		if (rlt > 0)
		{
			if ((*bffr)[rlt - 1] == '\n')
			{
				(*bffr)[rlt - 1] = '\0'; /* remove trailing newline */
				rlt--;
			}
			shellInfo->linecount_flag = 1;
			_remvCmnts(*bffr);
			_buildHistList(shellInfo, *bffr, shellInfo->histcount++);
			/* if (_charStr(*bffr, ';')) is this a command chain? */
			{
				*len = rlt;
				shellInfo->cmd_buf = bffr;
			}
		}
	}
	return (rlt);
}

/**
 * _getInput - gets a line minus the newline
 * @shellInfo: parameter struct
 *
 * Return: bytes read
 */
ssize_t _getInput(info_t *shellInfo)
{
	static char *bffr; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t rlt = 0;
	char **bffrp = &(shellInfo->arg), *p;

	_putChar(BUF_FLUSH);
	rlt = input_buf(shellInfo, &bffr, &len);
	if (rlt == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current bffr position */
		p = bffr + i; /* get pointer for return */

		_checkChain(shellInfo, bffr, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (_isChainDelm(shellInfo, bffr, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			shellInfo->cmd_buf_type = CMD_NORM;
		}

		*bffrp = p; /* pass back pointer to current command position */
		return (_lengthStr(p)); /* return length of current command */
	}

	*bffrp = bffr; /* else not a chain, pass back buffer from _getLine() */
	return (rlt); /* return length of buffer from _getLine() */
}

/**
 * read_buf - reads a buffer
 * @shellInfo: parameter struct
 * @bffr: buffer
 * @i: size
 *
 * Return: rlt
 */
ssize_t read_buf(info_t *shellInfo, char *bffr, size_t *i)
{
	ssize_t rlt = 0;

	if (*i)
		return (0);
	rlt = read(shellInfo->readfd, bffr, READ_BUF_SIZE);
	if (rlt >= 0)
		*i = rlt;
	return (rlt);
}

/**
 * _getLine - gets the next line of input from STDIN
 * @shellInfo: parameter struct
 * @ptb: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptb buffer if not NULL
 *
 * Return: s
 */
int _getLine(info_t *shellInfo, char **ptb, size_t *length)
{
	static char bffr[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t rlt = 0, s = 0;
	char *p = NULL, *newp = NULL, *c;

	p = *ptb;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	rlt = read_buf(shellInfo, bffr, &len);
	if (rlt == -1 || (rlt == 0 && len == 0))
		return (-1);

	c = _charStr(bffr + i, '\n');
	k = c ? 1 + (unsigned int)(c - bffr) : len;
	newp = _reallocMem(p, s, s ? s + k : k + 1);
	if (!newp) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_concnStr(newp, bffr + i, k - i);
	else
		_copynStr(newp, bffr + i, k - i + 1);

	s += k - i;
	i = k;
	p = newp;

	if (length)
		*length = s;
	*ptb = p;
	return (s);
}

/**
 * _sgntHndler - blocks ctrl-C
 * @signmbr: the signal number
 *
 * Return: void
 */
void _sgntHndler(__attribute__((unused))int signmbr)
{
	_putStr("\n");
	_putStr("$ ");
	_putChar(BUF_FLUSH);
}

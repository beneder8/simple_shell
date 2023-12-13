#include "shell.h"

/**
 * main - entry point
 * @argcnt: arg count
 * @argvctr: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argcnt, char **argvctr)
{
	info_t shellInfo[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (argcnt == 2)
	{
		fd = open(argvctr[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_printErrorStr(argvctr[0]);
				_printErrorStr(": 0: Can't open ");
				_printErrorStr(argvctr[1]);
				_printErrorChar('\n');
				_printErrorChar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		shellInfo->readfd = fd;
	}
	_pptEnvList(shellInfo);
	_readHist(shellInfo);
	_shellLoop(shellInfo, argvctr);
	return (EXIT_SUCCESS);
}

#include "shell.h"

/**
 * hsh - main shell loop
 * @firstinfo: the parameter & return informa struct
 * @ve: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *firstinfo, char **ve)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(firstinfo);
		if (interactive(firstinfo))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(firstinfo);
		if (r != -1)
		{
			set_info(firstinfo, ve);
			builtin_ret = find_builtin(firstinfo);
			if (builtin_ret == -1)
				find_cmd(firstinfo);
		}
		else if (interactive(firstinfo))
			_putchar('\n');
		free_info(firstinfo, 0);
	}
	write_history(firstinfo);
	free_info(firstinfo, 1);
	if (!interactive(firstinfo) && firstinfo->status)
		exit(firstinfo->status);
	if (builtin_ret == -2)
	{
		if (firstinfo->err_num == -1)
			exit(firstinfo->status);
		exit(firstinfo->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @firstinfo: the parameter & return firstinfo struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_t *firstinfo)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(firstinfo->argv[0], builtintbl[i].type) == 0)
		{
			firstinfo->line_count++;
			built_in_ret = builtintbl[i].func(firstinfo);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @firstinfo: the parameter & return firstinfo struct
 *
 * Return: void
 */
void find_cmd(info_t *firstinfo)
{
	char *path = NULL;
	int i, k;

	firstinfo->path = firstinfo->argv[0];
	if (firstinfo->linecount_flag == 1)
	{
		firstinfo->line_count++;
		firstinfo->linecount_flag = 0;
	}
	for (i = 0, k = 0; firstinfo->arg[i]; i++)
		if (!is_delim(firstinfo->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(firstinfo, _getenv(firstinfo, "PATH="), firstinfo->argv[0]);
	if (path)
	{
		firstinfo->path = path;
		fork_cmd(firstinfo);
	}
	else
	{
		if ((interactive(firstinfo) || _getenv(firstinfo, "PATH=")
			|| firstinfo->argv[0][0] == '/') && is_cmd(firstinfo, firstinfo->argv[0]))
			fork_cmd(firstinfo);
		else if (*(firstinfo->arg) != '\n')
		{
			firstinfo->status = 127;
			print_error(firstinfo, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @firstinfo: the parameter & return firstinfo struct
 *
 * Return: void
 */
void fork_cmd(info_t *firstinfo)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(firstinfo->path, firstinfo->argv, get_environ(firstinfo)) == -1)
		{
			free_info(firstinfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(firstinfo->status));
		if (WIFEXITED(firstinfo->status))
		{
			firstinfo->status = WEXITSTATUS(firstinfo->status);
			if (firstinfo->status == 126)
				print_error(firstinfo, "Permission denied\n");
		}
	}
}

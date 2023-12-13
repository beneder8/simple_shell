#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for _cnvrtNmbr() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct lists - singly linked list
 * @nmbr: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct lists
{
	int nmbr;
	char *str;
	struct lists *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* hsh.c */
int hsh(info_t *, char **);
int _findBuiltin(info_t *);
void _findCommand(info_t *);
void _forkCommand(info_t *);

/* pathFile.c */
int _execuCommand(info_t *, char *);
char *_dupCharacters(char *, int, int);
char *_fndPath(info_t *, char *, char *);

/* loopHsh.c */
int _loopHsh(char **);

/* errStrFunctions.c */
void _printErrorStr(char *);
int _printErrorChar(char);
int _writeCharToFD(char r, int filedsc);
int _printStrToFD(char *str, int filedsc);

/* funcString.c */
int _lengthStr(char *);
int _compStr(char *, char *);
char *_startWith(const char *, const char *);
char *_concStr(char *, char *);

/* funcString2.c */
char *_copyStr(char *, char *);
char *_duplictStr(const char *);
void _putStr(char *);
int _putChar(char);

/* funcString3.c */
char *_copynStr(char *, char *, int);
char *_concnStr(char *, char *, int);
char *_charStr(char *, char);

/* funcString4.c */
char **_towordStr(char *, char *);
char **_towordStr2(char *, char);

/* funcMemory.c */
char *_setMemory(char *, char, unsigned int);
void _freeStr(char **);
void *_reallocMem(void *, unsigned int, unsigned int);

/* funcMemory2.c */
int _bfree(void **);

/* moreFuncs.c */
int _isInteractv(info_t *);
int _isDelimtr(char, char *);
int _isAlphabt(int);
int _strToInt(char *);

/* moreFuncs2.c */
int _strToInt2(char *);
void _prntError(info_t *, char *);
int _prntDec(int, int);
char *_cnvrtNmbr(long int, int, int);
void _remvCmnts(char *);

/* emulsBuilt.c */
int _exitShell(info_t *);
int _changeDirectory(info_t *);
int _showHelp(info_t *);

/* emulsBuilt2.c */
int _dispHistory(info_t *);
int _mAlias(info_t *);

/* getLine.c */
ssize_t _getInput(info_t *);
int _getLine(info_t *, char **, size_t *);
void _sgntHndler(int);

/* clearInfo.c */
void _clearInfo(info_t *);
void _setInfo(info_t *, char **);
void _freeInfo(info_t *, int);

/* envirn.c */
char *_getEnvirn(info_t *, const char *);
int _thisEnvirn(info_t *);
int _setEnvirn(info_t *);
int _unSetEnvirn(info_t *);
int _pptEnvList(info_t *);

/* envirn2.c */
char **_getEnviron(info_t *);
int _unsetEnvr(info_t *, char *);
int _setEnvr(info_t *, char *, char *);

/* ioFile.c */
char *_getHistFile(info_t *shellInfo);
int _writeHist(info_t *shellInfo);
int _readHist(info_t *shellInfo);
int _buildHistList(info_t *shellInfo, char *bffr, int linecnt);
int _renmbrHist(info_t *shellInfo);

/* lists.c */
list_t *_nodeStart(list_t **, const char *, int);
list_t *_nodeEnd(list_t **, const char *, int);
size_t _prntListStr(const list_t *);
int _delNodeIndex(list_t **, unsigned int);
void _freeList(list_t **);

/* lists2.c */
size_t _lenghtList(const list_t *);
char **_listToStr(list_t *);
size_t _prntList(const list_t *);
list_t *_nodeStartWith(list_t *, char *, char);
ssize_t _getNodeIndex(list_t *, list_t *);

/* chainVars.c */
int _isChainDelm(info_t *, char *, size_t *);
void _checkChain(info_t *, char *, size_t *, size_t, size_t);
int _replaceAlias(info_t *);
int _replaceVar(info_t *);
int _replaceStr(char **, char *);

#endif

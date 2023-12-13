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

/* functions_str.c */
int _showLem(char *);
int _toCmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strAdd(char *, char *);

/* functions_str2.c */
char *_strmul(char *, char *);
char *_str_duplicat(const char *);
void _puts(char *);
int _putchar(char);

/* functions_str3.c */
char *_str_copy(char *, char *, int);
char *_str_concatenated(char *, char *, int);
char *_strchr(char *, char);

/* functions_str4.c */
char **strCheck(char *, char *);
char **strCheck2(char *, char);

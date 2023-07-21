#ifndef MAIN_H
#define MAIN_H

#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>

/* com chain */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* read and write */
#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1

/* conv_numbers */

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* sys getline */
#define USE_STRTOK 0
#define USE_GETLINE 0

#define HIST_FILE 	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: the string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
* struct passinfo - contains pseudo-arguments to pass into a function,
* allowing uniform prototype for function pointer struct.
* @arg: a string generated from getline containing arguments.
* @argv: an array of strings generated from arg.
* @path: a string path for the current command.
* @argc: the argument count.
* @line_count: the error count.
* @err_num: the error code for exit(s)
* @linecount_flag: if on count this line of input.
* @fname: the program file name.
* @env: linked list local copy of environ.
* @environ: custom modified copy of environ from LL env.
* @history: the history node.
* @alias: the alias node.
* @env_changed: on if environ was changed.
* @status: the return status of the last exec'd command.
* @cmd_buf: address of pointer to cmd_buff, on if chaining.
* @cmd_buf_type: CMD_type ||, &&, ;
* @readfd: the fd from which to read line input
* @histcount: the history line number count.
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
       

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory management */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}

/**
* struct builtin - contains a builtin string and related function.
* @type: the builtin command flag.
* @func: the function.
*/
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* chto.c */
int interactive_mode(info_t *info);
int delime(char a, char *deli);
int foraplha(int z);
int chtoi(char *a);
#endif

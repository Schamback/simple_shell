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
int ifree(void **ptr);
int is_dmz(info_t *info, char *path);
<<<<<<< HEAD
	
=======
int gethist(info_t *info);

/* enviton.c */
int p_env(info_t *info);
char *get_env(info_t *info, const char *name);
int set_env(info_t *info);
int rems_env(info_t *info);
int mult_env_list(info_t *info);

/* errors.c */
int put_fd(char *str, int fd);
int _putfd(char y, int fd);
int p_char(char w);
void p_string(char *str);

/* exits.c */
char *loc_str(char *r, char b);
char *con_char(char *dest, char *src, int p);
char *cpy_str(char *dest, char *src, int t);

/* getline.c */
void sigintBlock(__attribute__((unused))int sig_num);
int get_next(info_t *info, char **ptr, size_t *length);
ssize_t rid_buf(info_t *info, char *buf, size_t *s);
ssize_t get_line(info_t *info);
ssize_t comm_buf(info_t *info, char **buf, size_t *len);

/* getenviron */
int set_envo(info_t *info, char *var, char *value);
int rem_env(info_t *info, char *var);
char **environ_get(info_t *info);

/* gethistory */
void info_free(info_t *info, int all);
void sets_info(info_t *info, char **av);
void clears_info(info_t *info);

/* list.c */
void free_node(list_t **head_ptr);
int delete_at_index(list_t **head, unsigned int index);
size_t print_str(const list_t *a);
list_t *add_end(list_t **head, const char *str, int num);
list_t *_addNode(list_t **head, const char *str, int num);

/* history.c */
int renumber_hist(info_t *info);
int add_history(info_t *info, char *buf, int linecount);
int read_hist(info_t *info);
int write_hist(info_t *info);
char *get_history(info_t *info);

/*builtin0.c */
int shexit(info_t *info);
int cd_change(info_t *info);
int ushelp_(info_t *info);

/*builtin2.c */
int cp_alias(info_t *info);
int p_alias(list_t *node);
int place_alias(info_t *info, char *str);
int form_alias(info_t *info, char *str);
int gethist(info_t *info);

/* errors2.c */
int _erratois(char *w);
void gives_error(info_t *info, char *estr);
int print_dec(int input, int fd);
char *convert_num(long int num, int base, int flags);
void delete_comments(char *buff);

>>>>>>> 52dc20837f382afce4e5a0f2d1fcc02f0958335f
#endif

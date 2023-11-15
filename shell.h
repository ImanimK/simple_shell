#ifndef _SHELL_H_
#define _SHELL_H_

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

/* Read/write buffers sizes */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Command chaining types */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* Conversion options for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* Flag for using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - Singly linked list.
 * @num: The number of field.
 * @str: String.
 * @next: Points to node coming next.
 */
typedef struct liststr
{
int num;
char *str;
struct liststr *next;
} list_t;

/**
 *struct passinfo - Contains pseudo-arguements passing into function.
 *		Allowing uniform prototype function pointer struct.
 *@arg: String generated from getline containing arguements.
 *@argv: Array of strings generated from arg.
 *@path: String path for current command.
 *@argc: Argument count.
 *@line_count: Error count.
 *@err_num: Error code for exit()s.
 *@linecount_flag: On count this line of input.
 *@fname: Program filename.
 *@env: The linked list local copy of environ.
 *@environ: Custom modified copy of environ from LL env.
 *@history: History node.
 *@alias: Alias node.
 *@env_changed: Turns on if environ changed.
 *@status: Return status of last executed command.
 *@cmd_buf: Address of pointer to cmd_buf, turns on if chaining.
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: Fd from where to read line input.
 *@histcount: History line number count.
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
 *struct builtin - Contains builtin string also related function.
 *@type: Builtin command flag.
 *@func: Function.
 */
typedef struct builtin
{
char *type;
int (*func)(info_t *);
} builtin_table;


/* Shell Loop Functions */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* Parser Functions */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* Main Loop Function */
int loophsh(char **);

/* Error Handling Functions */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* String Handling Functions */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* String Handling Functions (part 2) */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* Exit Functions */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* Tokenization Functions */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* Memory Reallocation Functions */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* Memory Management Functions */
int bfree(void **);

/* Numeric Conversion Functions */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* Error Handling Functions(part 2) */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* Built-in Functions */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* Built-in Functions (part 2) */
int _myhistory(info_t *);
int _myalias(info_t *);

/* Get Line Functions */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* Information Handling Functions */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* Environ Functions */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* Get Environ Functions */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* History Functions */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* Lists Functions */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* Lists Functions(part 2) */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* Vars Funstions */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif


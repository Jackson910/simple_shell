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

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
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
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* loop.c */
int main_shell_loop(info_t *, char **);
int find_and_execute_builtin(info_t *);
void find_and_execute_command(info_t *);
void fork_and_execute_command(info_t *);

/* isexecutable.c */
int is_executable(info_t *, char *);
char *extract_substring(char *, int, int);
char *find_command_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* checks.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* string.c */
int string_length(char *);
int string_compare(char *, char *);
char *string_starts_with(const char *, const char *);
char *string_concatenate(char *dest, char *src);

/* string1.c */
char *_string_copy(char *, char *);
char *_string_duplicate(const char *);
void _print_string(char *);
int _putchar(char);

/* end.c */
char *_strncpy(char *dest, const char *src, size_t n);
char *_strchr(char *, char);

/* token.c */
char **split_string_with_delimiter(char *, char *);
char **split_string_with_single_delimiter(char *, char);

/* memset.c */
char *_memset_memory(char *, char, unsigned int);
void free_string_array(char **);
void *_realloc_memory(void *, unsigned int, unsigned int);

/* freeMemory.c */
int safeFree(void **);

/* isalpha.c */
int check_interactive_mode(info_t *);
int is_delimiter(char, char *);
int is_alphabetic(int);
int string_to_integer(char *);

/* checks1.c */
int _strtoi(char *);
int print_integer(int input, int fd);
void print_error(info_t *info, char *error_msg);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* inbuilt.c */
int exit_shell(info_t *);
int change_directory(info_t *);
int show_help(info_t *);

/* inbuilt1.c */
int print_history(info_t *);
int manage_alias(info_t *info);
int unset_alias(info_t *info, char *alias_name);
int set_alias(info_t *info, char *alias_str);
int print_alias(list_t *alias_node);

/* getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* getinfo.c */
void initializeInfo(info_t *);
void setInfo(info_t *, char **);
void freeInfo(info_t *, int);

/* env.c */
char *get_environment_variable(info_t *, const char *);
int print_environment(info_t *);
int _myset_environment(info_t *);
int _myunset_environment(info_t *);
int initialize_environment_list(info_t *);

/* environment.c */
char **getEnvironment(info_t *);
int unsetEnvironmentVar(info_t *, char *);
int setEnvironmentVar(info_t *, char *, char *);

/* history.c */
char *getHistoryFile(info_t *info);
int writeHistory(info_t *info);
int readHistory(info_t *info);
int buildHistoryList(info_t *info, char *buf, int linecount);
int renumberHistory(info_t *info);

/* node.c */
list_t *addNode(list_t **, const char *, int);
list_t *addNodeEnd(list_t **, const char *, int);
size_t printListStr(const list_t *);
int deleteNodeAtIndex(list_t **, unsigned int);
void freeList(list_t **);

/* node1.c */
size_t listLength(const list_t *);
char **listToStrings(list_t *);
size_t printList(const list_t *);
list_t *findNodeWithPrefix(list_t *, char *, char);
ssize_t getNodeIndex(list_t *, list_t *);

/* variables.c */
int is_command_chaining(info_t *, char *, size_t *);
void check_command_chaining(info_t *, char *, size_t *, size_t, size_t);
int replace_aliases(info_t *);
int replace_variables(info_t *);
int replace_string(char **, char *);


#endif

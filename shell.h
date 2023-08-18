#ifndef SHELL_H
#define SHELL_H

#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <limits.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stddef.h>

#define BUF_SIZE 1024
#define TOKEN_BUF_SIZE 128
#define TOKEN_DELIM " \t\r\n\a"

/* pointer to array of pointers of string(environment) */
extern char **environ;

/**
 * struct p_list_op - singly linked list
 * @next: The next node
 * @oper: the operators |, & and ;
 */
typedef struct p_list_op
{
	char oper;
	struct p_list_op *next;
} list_op;

/**
 * struct line_list_ln -linked list
 * @line: command line
 * @next: next node
 */
typedef struct line_list_ln
{
	char *line;
	struct line_list_ln *next;
} list_ln;

/**
 * struct shell_data - struct that with required data for shell
 * @av: vector argument
 * @input: command entered by user
 * @args: arguments
 * @_environ: variable environment
 * @pid: process ID
 * @status: last status of the shell
 * @counter: counts lines
 */
typedef struct shell_data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} list_sh;

/**
 * struct r_list_var - linked list
 * @var_len: variable length
 * @val: value of variable
 * @val_len: length of value
 * @next: next node
 */
typedef struct r_list_var
{
	int var_len;
	char *val;
	int val_len;
	struct r_list_var *next;
} list_var;

/**
 * struct builtin_s - Builtin struct command for args.
 * @name: The name of the command builtin
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(list_sh *info);
} builtin_t;

/* environ.c */
int comp_env(const char *env_name, const char *name);
char *get_env(const char *name, char **_environ);
int print_env(list_sh *info);
int _setenv(list_sh *info);
void setEnv(char *name, char *value, list_sh *info);

/* environ2.c */
char *_copyinfo(char *name, char *value);
int _unsetenv(list_sh *info);

/* getline.c */
char *print_str(int *_eof);
void ass_line(char **ptr, size_t *n, char *str, size_t j);
ssize_t get_line(char **ptr, size_t *n, FILE *stream);

/* lists1.c */
list_ln *add_line_end(list_ln **head, char *line);
void free_list_ln(list_ln **head);
list_op *add_op_end(list_op **head, char op);
void free_list_op(list_op **head);

/* lists2.c */
list_var *add_var_end(list_var **head, int len_var, char *val, int len_val);
void free_list_var(list_var **head);

/* memory.c */
void _memcpy(void *dest, const void *src, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **realloc_dptr(char **ptr, unsigned int old_size, unsigned int new_size);

/* myBuiltin1.c */
void info_envbuiltin(void);
void set_envbuiltin(void);
void unset_envbuiltin(void);
void entry_info_env(void);
void info_exitbuiltin(void);

/* myBuiltin2.c */
void info_helpbuiltin(void);
void info_cdbuiltin(void);
void info_alias(void);
int (*get_builtin(char *cmd))(list_sh *);
int print_help(list_sh *info);

/* myCommands.c */
int command_exec(list_sh *info);
int check_ecmd(char *dir, list_sh *info);
char *loc_cmd(char *cmd, char **_environ);
int _isexecutable(list_sh *info);
int _iscdir(char *path, int *index);

/* myError1.c */
char *strcat_error(list_sh *info, char *msg, char *error, char *str);
char *exit_sh_error(list_sh *info);
char *no_error(list_sh *info);
char *cd_error(list_sh *info);

/* myError2.c */
int get_error(list_sh *info, int err_val);
char *env_error(list_sh *info);
char *path_126_error(list_sh *info);

/* myError3.c */
int check_esyntax(list_sh *info, char *input);
void print_esyntax(list_sh *info, char *input, int index, int bool);
int first_char(char *input, int *index);
int op_error(char *input, int index, char last);
int char_repeated(char *input, int index);

/* myExit.c */
int exit_sh(list_sh *info);
int line_exec(list_sh *info);
void get_sigint(int sig);

/* mydir.c */
int cd_current(list_sh *info);
void cd_home(list_sh *info);
void cd_back(list_sh *info);
void cd_dot(list_sh *info);
void cd_to(list_sh *info);

/* shell.c */
void _loopsh(list_sh *info);
char *del_comment(char *str);
void print_data(list_sh *info, char **av);
void free_data(list_sh *info);

/* string1.c */
char *_strcat(char *dest, const char *src);
int _strcmp(char *s1, char *s2);
int _strspn(char *s, char *accept);
char *_strchr(char *s, char c);
char *_strcpy(char *dest, char *src);

/* string2.c */
void _revString(char *s);
char *_strdup(const char *s);
int _strlen(const char *s);
char *_strtok(char str[], const char *delim);

/* string3.c */
int comp_char(char str[], const char *delim);
int _isdigit(const char *s);
int _atoi(char *s);
char *aux_itoa(int n);
int _getlen(int n);

/* tokenizer.c */
char **get_token(char *input);
void add_nodes(list_op **head_op, list_ln **head_ln, char *input);
char *_swapchar(char *input, int bool);
void go_to_next(list_op **list_p, list_ln **list_l, list_sh *info);
int _splitcmd(list_sh *info, char *input);

/* var.c */
char *replace_var(char *input, list_sh *info);
char *rep_input(list_var **head, char *input, char *str, int len);
int _checkvar(list_var **head, char *str, char *st, list_sh *data);
void _checkenv(list_var **head, char *str, list_sh *data);


#endif

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

#define BUF_SIZE 1024
#define TOKEN_BUF_SIZE 128
#define TOKEN_DELIM " \t\r\n\a"

/* pointer to array of pointers of string(environment) */
extern char **environ

/**
 * struct list_op - singly linked list
 * @next: The next node
 * @oper: the operators |, & and ;
 */
typedef struct list_op
{
	char oper;
	struct list_op *next;
} list_op;

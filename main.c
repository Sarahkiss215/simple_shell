#include "shell.h"

/**
 * main - main function
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	list_sh info;
	(void) ac;

	signal(SIGINT, get_sigint);
	print_data(&info, av);
	_loopsh(&info);
	free_data(&info);
	if (info.status < 0)
		return (255);
	return (info.status);
}


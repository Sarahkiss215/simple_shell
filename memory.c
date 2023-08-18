#include "shell.h"

/**
 * _memcpy - copies memory between void pointers.
 * @dest: destination pointer.
 * @src: source pointer.
 * @size: size of the new pointer.
 *
 * Return: Nothing.
 */
void _memcpy(void *dest, const void *src, unsigned int size)
{
	char *ptr1 = (char *)src;
	char *ptr2 = (char *)dest;
	unsigned int index = 0;

	for (; index < size; index++)
		ptr2[index] = ptr1[index];
}

/**
 * *_realloc - reallocates a memory block.
 * @ptr: pointer to the memory previously allocated.
 * @old_size: size of ptr.
 * @new_size: new size of the new memory block.
 *
 * Return: ptr is successful, NULL otherwise.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *allo_mem;

	if (ptr == NULL)
	{
		return (malloc(new_size));
	}
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == old_size)
	{
		return (ptr);
	}
	allo_mem = malloc(new_size);
	if (allo_mem == NULL)
	{
		return (NULL);
	}
	if (new_size < old_size)
	{
		_memcpy(allo_mem, ptr, new_size);
	}
	else
		_memcpy(allo_mem, ptr, old_size);
	free(ptr);
	return (allo_mem);
}

/**
 * **realloc_dptr - reallocates a memory block of a double pointer.
 * @ptr: double pointer to the memory previously allocated.
 * @old_size: size of ptr.
 * @new_size: new size of the new memory block.
 *
 * Return: ptr if successful, NULL otherwise.
 */
char **realloc_dptr(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **allo_mem;
	unsigned int index = 0;

	if (ptr == NULL)
	{
		return (malloc(sizeof(char *) * new_size));
	}
	if (new_size == old_size)
	{
		return (ptr);
	}
	allo_mem = malloc(sizeof(char *) * new_size);
	if (allo_mem == NULL)
	{
		return (NULL);
	}
	for (; index < old_size; index++)
	{
		allo_mem[index] = ptr[index];
	}
	free(ptr);
	return (allo_mem);
}

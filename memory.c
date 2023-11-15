#include "shell.h"

/**
 * bfree - Releases memory occupied by a pointer and sets it to NULL.
 * @ptr: Address of the pointer to be free.
 *
 * Return: 1 if memory is freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}


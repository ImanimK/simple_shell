#include "shell.h"

/**
 **_memset - Fills a block of memory with a constant byte.
 *@s: Pointer to the memory area.
 *@b: The byte to fill the memory with.
 *@n: The number of bytes to be filled.
 *Return: (s) A pointer to the memory area.
 */
char *_memset(char *s, char b, unsigned int n)
{
unsigned int i;
for (i = 0; i < n; i++)
s[i] = b;
return (s);
}

/**
 * ffree - Frees a dynamic array of strings.
 * @pp: The array of strings.
 */
void ffree(char **pp)
{
char **a = pp;
if (!pp)
return;
while (*pp)
free(*pp++);
free(a);
}

/**
 * _realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previous dynamically allocated block.
 * @old_size: Size of the previous block in bytes.
 * @new_size: Size of the new block in bytes.
 *
 * Return: Pointer to the reallocated block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
char *p;
if (!ptr)
return (malloc(new_size));
if (!new_size)
return (free(ptr), NULL);
if (new_size == old_size)
return (ptr);
p = malloc(new_size);
if (!p)
return (NULL);
old_size = old_size < new_size ? old_size : new_size;
while (old_size--)
p[old_size] = ((char *)ptr)[old_size];
free(ptr);
return (p);
}


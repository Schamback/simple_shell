#include "main.h"

/**
 **_nameset - fills memory with a constant byte
 *@l: the pointer to the memory area
 *@p: the byte to fill *s with
 *@m: the amount of bytes to be filled
 *Return: (l) a pointer to the memory area s
 */
char *_nameset(char *l, char p, unsigned int m)
{
	unsigned int i;

	for (i = 0; i < m; i++)
		l[i] = p;
	return (l);
}

/**
 * pfree - frees a string of strings
 * @pp: string of strings
 */
void pfree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _dealoc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_dealoc(void *ptr, unsigned int old_size, unsigned int new_size)
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

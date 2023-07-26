#include "main.h"

/**
 * _stcpy - copies a string
 * @rest: the destination
 * @prc: the source
 *
 * Return: pointer to destination
 */
char *_stcpy(char *rest, char *prc)
{
	int i = 0;

	if (rest == prc || prc == 0)
		return (rest);
	while (prc[i])
	{
		rest[i] = prc[i];
		i++;
	}
	rest[i] = 0;
	return (rest);
}

/**
 * _stdup - duplicates a string
 * @spr: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_stdup(const char *spr)
{
	int length = 0;
	char *ret;

	if (spr == NULL)
		return (NULL);
	while (*spr++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--spr;
	return (ret);
}

/**
 *_puts - prints an input string
 *@spr: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *spr)
{
	int i = 0;

	if (!spr)
		return;
	while (spr[i] != '\0')
	{
		_putchar(spr[i]);
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @d: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char d)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (d != BUF_FLUSH)
		buf[i++] = d;
	return (1);
}

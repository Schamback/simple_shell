#include "main.h"

/**
* *p_string - prints an input string
* @str: the string to be printed
* Return: Nothing
*/
void p_string(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		putchar(str[i]);
		i++;
	}
}

/**
* p_char - writes the character w to stderr
*  @w: The character to print
*  Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int p_char(char w)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (w == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, buf, a);
		a = 0;
	}
	if (w != BUF_FLUSH)
		buf[a++] = w;
	return (1);
}

/**
* put_fd - writes the character c to given fd
* @y: The character to print
* @fd: The filedescriptor to write to
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int _putfd(char y, int fd)
{
	static int s;
	static char buf[WRITE_BUF_SIZE];

	if (y == BUF_FLUSH || s >= WRITE_BUF_SIZE)
	{
		write(fd, buf, s);
		s = 0;
	}
	if (y != BUF_FLUSH)
		buf[s++] = y;
	return (1);
}

/**
* put_fd - prints an input string
* @str: the string to be printed
* @fd: the filedescriptor to write to
* eturn: the number of chars put
*/
int put_fd(char *str, int fd)
{
	int x = 0;

	if (!str)
		return (0);
	while (*str)
	{
		x += _putfd(*str++, fd);
	}
	return (x);
}

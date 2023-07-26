#include "main.h"

/**
* *cpy_str - copies a string
* @dest: the destination string to be copied to
* @src: the source string
* @t: the amount of characters to be copied
* Return: the concatenated string
*/
char *cpy_str(char *dest, char *src, int t)
{
	int a, g;
	char *k = dest;

	a = 0;
	while (src[a] != '\0' && a < t - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < t)
	{
		g = a;
		while (g < t)
		{
			dest[g] = '\0';
			g++;
		}
	}
	return (k);
}

/**
* *con_char - concatenates two strings
* @dest: the first string
* @src: the second string
* @p: the amount of bytes to be maximally used
* Return: the concatenated string
*/
char *con_char(char *dest, char *src, int p)
{
	int a, g;
	char *s = dest;

	a = 0;
	g = 0;
	while (dest[a] != '\0')
		a++;
	while (src[g] != '\0' && g < p)
	{
		dest[a] = src[g];
		a++;
		g++;
	}
	if (g < p)
		dest[a] = '\0';
	return (s);
}

/**
* *loc_str - locates a character in a string
* @r: the string to be parsed
* @b: the character to look for
* Return: (r) a pointer to the memory area s
*/
char *loc_str(char *r, char b)
{
	do {
		if (*r == b)
			return (r);
	} while (*r++ != '\0');

	return (NULL);
}

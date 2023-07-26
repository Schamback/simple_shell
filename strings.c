#include "main.h"

/**
 * _stlen - returns the length of a string
 * @r: the string whose length to check
 *
 * Return: integer length of string
 */
int _stlen(char *r)
{
	int i = 0;

	if (!r)
		return (0);

	while (*r++)
		i++;
	return (i);
}

/**
 * _stcmp - performs lexicogarphic comparison of two strangs.
 * @r1: the first strang
 * @r2: the second strang
 *
 * Return: negative if r1 < r2, positive if r1 > r2, zero if r1 == r2
 */
int _stcmp(char *r1, char *r2)
{
	while (*r1 && *r2)
	{
		if (*r1 != *r2)
			return (*r1 - *r2);
		r1++;
		r2++;
	}
	if (*r1 == *r2)
		return (0);
	else
		return (*r1 < *r2 ? -1 : 1);
}

/**
 * stats_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *stats_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _stcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_stcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

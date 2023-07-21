#include "main.h"

/**
 * interactive_mode - returns true if shell is interactive mode
 * @info: struct address
 * Return: 1 if interactive mode, 0 otherwise
 */

int interactive_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * delime - checks char is a delimeter.
 * @a: the char to be checked
 * @deli: the delimeter string
 * Return: 1 if true, 0 if false
 */
int delime(char  a, char *deli)
{
	while (*deli)
		if (*deli++ == a)
			return (1);
	return (0);
}

/**
 * foralpha - checks for alphabetic char
 * @z: The char to be input
 * Return: 1 if z is alpha, 0 otherwise
 */
int foralpha(int z)
{
	if ((z >= 'a' && z <= 'z') || (z >= 'A' && z <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * chtoi - converts string to integer
 * @a: string to be converted
 * Return: 0 if no number in string, converted number otherwise
 */
int chtoi(char *a)
{
	int w, sign = 1, flag = 0, outputs;
	unsigned int results = 0;

	for (w = 0; a[w] != '\0' && flag != 2; w++)
	{
		if (a[w] == '-')
			sign *= -1;
		if (a[w] >= '0' && a[w] <= '9')
		{
			flag = 1;
			results *= 10;
			results += (a[w] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		outputs = -results;
	else
		outputs = results;
	return (outputs);
}

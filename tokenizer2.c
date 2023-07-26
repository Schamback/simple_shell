#include "main.h"

/**
 * **stow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @g: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **stow(char *str, char *g)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!g)
		g = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], g) && (is_delim(str[i + 1], g) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], g))
			i++;
		k = 0;
		while (!is_delim(str[i + k], g) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **stow2 - splits a string into words
 * @str: the input string
 * @g: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char g)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != g && str[i + 1] == g) ||
		    (str[i] != g && !str[i + 1]) || str[i + 1] == g)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == g && str[i] != g)
			i++;
		k = 0;
		while (str[i + k] != g && str[i + k] && str[i + k] != g)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

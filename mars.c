#include "main.h"

/**
 * is_brain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_brain(info_t *info, char *buf, size_t *p)
{
	size_t s = *p;

	if (buf[s] == '|' && buf[s + 1] == '|')
	{
		buf[s] = 0;
		s++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[s] == '&' && buf[s + 1] == '&')
	{
		buf[s] = 0;
		s++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[s] == ';') /* found end of this command */
	{
		buf[s] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = s;
	return (1);
}

/**
 * check_brain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @b: address of current position in buf
 * @y: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_brain(info_t *info, char *buf, size_t *b, size_t y, size_t len)
{
	size_t s = *b;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			s = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			s = len;
		}
	}

	*b = s;
}

/**
 * replace_elias - replaces an eliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_elias(info_t *info)

	int y;
	list_t *node;
	char *b;

	for (y = 0; y< 10; y++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		b = _strchr(node->str, '=');
		if (!b)
			return (0);
		b = _strdup(b + 1);
		if (!b)
			return (0);
		info->argv[0] = b;
	}
	return (1);
}

/**
 * replace_mars - replaces mars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_mars(info_t *info)
{
	int y = 0;
	list_t *node;

	for (y = 0; info->argv[y]; y++)
	{
		if (info->argv[y][0] != '$' || !info->argv[y][1])
			continue;

		if (!_strcmp(info->argv[y], "$?"))
		{
			replace_string(&(info->argv[y]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[y], "$$"))
		{
			replace_string(&(info->argv[y]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[y][1], '=');
		if (node)
		{
			replace_string(&(info->argv[y]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[y], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

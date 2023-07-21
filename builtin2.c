#include "main.h"

/**
 * gethist - displays history list, one command by line
 * @info: struc containing arguments used to maintain
 * functions
 * Return: Always 0
 */
int gethist(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * form_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on fail
 */
int form_alias(info_t *info, char *str)
{
	char *g, w;
	int ter;

	g = strchr(str, '=');
	if (!g)
		return (1);
	w = *g;
	*g = 0;
	ter = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_start_with(info->alias, str, -1)));
	*g = w;
	return (ter);
}

/**
 * place_alias - set alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on fail
 */
int place_alias(info_t *info, char *str)
{
	char *e;

	e = strchr(str, '=');
	if (!e)
		return (1);
	if (!*++e)
		return (form_alias(info, str));

	form_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * p_alias - prints alias string
 * @node: the alias node
 * Return: Always 0 on success, 1 on fail
 */
int p_alias(list_t *node)
{
	char *i = NULL, *s = NULL;

	if (node)
	{
		i = strchr(node->str, '=');
		for (s = node->str; s <= i; s++)
			putchar(*s);
		putchar('\'');
		puts(i + 1);
		puts("'\n");
		return (0);
	}
	return (0);
}

/**
 * cp_alias - copy of alias builtin
 * @info: struct containing arguments used to maintain
 * functions
 * Return: Always 0
 */
int cp_alias(info_t *info)
{
	int k = 0;
	char *w = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			p_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (k = 1; info->argv[k]; k++)
	{
		w = strchr(info->argv[k], '=');
		if (w)
			place_alias(info, info->argv[k]);
		else
			p_alias(node_start_with(info->alias, info->argv[k], '='));
	}
	return (0);
}


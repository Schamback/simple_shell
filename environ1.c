#include "main.h"

/**
* p_env - prints the current environment
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int p_env(info_t *info)
{
	print_str(info->env);
	return (0);
}

/**
* get_env - gets the value of an environ variable
* @info: Structure containing potential arguments. Used to maintain
* @name: env var name
* Return: the value
*/
char *get_env(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *o;

	while (node)
	{
		o = starts_with(node->str, name);
		if (o && *o)
			return (o);
		node = node->next;
	}
	return (NULL);
}

/**
* set_env - Initialize a new environment variable,
* or modify an existing one
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int set_env(info_t *info)
{
	if (info->argc != 3)
	{
		puts("Incorrect number of arguements\n");
		return (1);
	}
	if (setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}
/**
* rem_env - Remove an environment variable
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int rems_env(info_t *info)
{
	int w;

	if (info->argc == 1)
	{
		puts("Too few arguements.\n");
		return (1);
	}
	for (w = 1; w <= info->argc; w++)
		rems_env(info, info->argv[w]);

	return (0);
}

/**
* mult_env_list - populates env linked list
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int mult_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t r;

	for (r = 0; environ[r]; r++)
		add_node_end(&node, environ[r], 0);
	info->env = node;
	return (0);
}

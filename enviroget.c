#include "main.h"

/**
* environ_get - returns the string array copy of our environ
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
char **environ_get(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
* rem_env - Remove an environment variable
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: 1 on delete, 0 otherwise
* @var: the string env var property
*/
int rem_env(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t t = 0;
	char *e;


	if (!node || !var)
		return (0);

	while (node)
	{
		e = starts_with(node->str, var);
		if (e && *e == '=')
		{
			info->env_changed = delete_at_index(&(info->env), t);
			t = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		t++;
	}
	return (info->env_changed);
}

/**
*  set_envo - Initialize a new environment variable,
* or modify an existing one
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* @var: the string env var property
* @value: the string env var value
* Return: Always 0
*/
int set_envo(info_t *info, char *var, char *value)
{
	char *buff = NULL;
	list_t *node;
	char *u;

	if (!var || !value)
		return (0);

	buff = malloc(strlen(var) + strlen(value) + 2);
	if (!buff)
		return (1);
	strcpy(buff, var);
	strcat(buff, "=");
	strcat(buff, value);
	node = info->env;
	while (node)
	{
		u = starts_with(node->str, var);
		if (u && *u == '=')
		{
			free(node->str);
			node->str = buff;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}


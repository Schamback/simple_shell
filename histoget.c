#include "main.h"

/**
* clears_info - initializes info_t struct
* @info: struct address
*/
void clears_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
* sets_info - initializes info_t struct
* @info: struct address
* @av: argument vector
*/
void sets_info(info_t *info, char **av)
{
	int p = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtoll(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (p = 0; info->argv && info->argv[p]; p++)
			;
		info->argc = p;

		place_alias(info);
		replace_vars(info);
	}
}

/**
* info_free - frees info_t struct fields
* @info: struct address
* @all: true if freeing all fields
*/
void info_free(info_t *info, int all)
{
	free(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		free(info->environ);
			info->environ = NULL;
		free((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		putchar(BUF_FLUSH);
	}
}

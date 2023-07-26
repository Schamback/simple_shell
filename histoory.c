#include "main.h"

/**
* get_history - gets the history file
* @info: parameter struct
* Return: allocated string containg history file
*/
char *get_history(info_t *info)
{
	char *buff, *di;

	di = getenv(info, "HOME=");
	if (!di)
		return (NULL);
	buff = malloc(sizeof(char) * (strlen(di) + strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	strcpy(buff, di);
	strcat(buff, "/");
	strcat(buff, HIST_FILE);
	return (buff);
}

/**
* write_hist - creates a file, or appends to an existing file
* @info: the parameter struct
* Return: 1 on success, else -1
*/
int write_hist(info_t *info)
{
	ssize_t fd;
	char *filename = get_history(info);
	list_t *node = NULL;


	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		put_fd(node->str, fd);
		_putfd('\n', fd);
	}
	putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
* read_hist - reads history from file
* @info: the parameter struct
* Return: histcount on success, 0 otherwise
*/
int read_hist(info_t *info)
{
	int a, lastt = 0, linescount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = get_history(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (a = 0; a < fsize; a++)
		if (buff[a] == '\n')
		{
			buff[a] = 0;
			add_history(info, buff + lastt, linescount++);
			lastt = a + 1;
		}
	if (lastt != a)
		add_history(info, buff + lastt, linescount++);
	free(buff);
	info->histcount = linescount;
	while (info->histcount-- >= HIST_MAX)
		delete_at_index(&(info->history), 0);
	renumber_hist(info);
	return (info->histcount);
}

/**
* add_history - adds entry to a history linked list
* @info: Structure containing potential arguments. Used to maintain
* @buf: buffer
* @linecount: the history linecount, histcount
* Return: Always 0
*/
int add_history(info_t *info, char *buf, int linecount)
{
	list_t *nodes = NULL;

	if (info->history)
		nodes = info->history;
	add_node_end(&nodes, buf, linecount);

	if (!info->history)
		info->history = nodes;
	return (0);
}

/**
* renumber_hist - renumbers the history linked list after changes
* @info: Structure containing potential arguments. Used to maintain
* Return: the new histcount
*/
int renumber_hist(info_t *info)
{
	list_t *node = info->history;
	int a = 0;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (info->histcount = a);
}

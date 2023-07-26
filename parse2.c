#include "main.h"

/**
 * is_dmz - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_dmz(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_marc - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_marc(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int m = 0, v = 0;

	for (v = 0, m = start; m < stop; m++)
		if (pathstr[m] != ':')
			buf[v++] = pathstr[m];
	buf[v] = 0;
	return (buf);
}

/**
 * find_map - finds this dmz in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @dmz: the dmz to find
 *
 * Return: full path of dmz if found or NULL
 */
char *find_map(info_t *info, char *pathstr, char *dmz)
{
	int m = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((strlen(dmz) > 2) && stats_with(dmz, "./"))
	{
		if (is_dmz(info, dmz))
			return (dmz);
}
	while (1)
	{
		if (!pathstr[m] || pathstr[m] == ':')
		{
			path = dup_marc(pathstr, curr_pos, m);
			if (!*path)
				strcat(path, dmz);
			else
			{
				_stcat(path, "/");
				strcat(path, dmz);
			}
			if (is_dmz(info, path))
				return (path);
			if (!pathstr[m])
				break;
			curr_pos = m;
		}
		m++;
	}
	return (NULL);
}

#include "main.h"

/**
* comm_buf - buffers chained commands
* @info: parameter struct
* @buf: address of buffer
* @len: address of len var
* Return: bytes read
*/
ssize_t comm_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t y = 0;
	size_t len_o = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		y = getline(buf, &len_o, stdin);
#else
		y = getline(info, buf, &len_o);
#endif
		if (y > 0)
		{
			if ((*buf)[y - 1] == '\n')
			{
				(*buf)[y - 1] = '\0';
				y--;
			}
			info->linecount_flag = 1;
			delete_comments(*buf);
			history_list(info, *buf, info->histcount++);
			/* if (strchr(*buf, ';')) is this a command chain? */
			{
				*len = y;
				info->cmd_buf = buf;
			}
		}
	}
	return (y);
}

/**
* get_line - gets a line minus the newline
* @info: parameter struct
* Return: bytes read
*/
ssize_t get_line(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t t, w, lem;
	ssize_t k = 0;
	char **buf_u = &(info->arg), *u;

	putchar(BUF_FLUSH);
	k = input_buf(info, &buf, &lem);
	if (k == -1) /* EOF */
		return (-1);
	if (lem)	/* we have commands left in the chain buffer */
	{
		w = t; /* init new iterator to current buf position */
		u = buf + t; /* get pointer for return */

		checks_chain(info, buf, &w, t, lem);
		while (w < lem) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &w))
				break;
			w++;
		}

		t = w + 1; /* increment past nulled ';'' */
		if (t >= lem) /* reached end of buffer? */
		{
			t = lem = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_u = u; /* pass back pointer to current command position */
		return (strlen(u)); /* return length of current command */
	}

	*buf_u = buf; /* else not a chain, pass back buffer from getline() */
	return (k); /* return length of buffer from getline() */
}

/**
* rid_buf - reads a buffer
* @info: parameter struct
* @buf: buffer
* @s: size
* Return: p
*/
ssize_t rid_buf(info_t *info, char *buf, size_t *s)
{
	ssize_t p = 0;

	if (*s)
		return (0);
	p = read(info->readfd, buf, READ_BUF_SIZE);
	if (p >= 0)
		*s = p;
	return (p);
}

/**
* get_next - gets the next line of input from STDIN
* @info: parameter struct
* @ptr: address of pointer to buffer, preallocated or NULL
* @length: size of preallocated ptr buffer if not NULL
* Return: s
*/
int get_next(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t w, len;
	size_t a;
	ssize_t x = 0, u = 0;
	char *q = NULL, *new_q = NULL, *c;


	q = *ptr;
	if (q && length)
		u = *length;
	if (w == len)
		w = len = 0;

	x = rid_buf(info, buf, &len);
	if (x == -1 || (x == 0 && len == 0))
		return (-1);

	c = strchr(buf + w, '\n');
	a = c ? 1 + (unsigned int)(c - buf) : len;
	new_q = realloc(q, u, u ? u + a : a + 1);
	if (!new_q) /* MALLOC FAILURE! */
		return (q ? free(q), -1 : -1);

	if (u)
		strncat(new_q, buf + w, a - w);
	else
		strncpy(new_q, buf + w, a - w + 1);
	u += a - w;
	w = a;
	q = new_q;

	if (length)
		*length = u;
	*ptr = q;
	return (u);
}

/**
* sigintBlock - blocks ctrl-C
* @sig_num: the signal number
* Return: void
*/
void sigintBlock(__attribute__((unused))int sig_num)
{
	puts("\n");
	puts("$ ");
	putchar(BUF_FLUSH);
}

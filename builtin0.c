#include "main.h"

/**
 * shexit - exits the shell.
 * @info: stru containing arguments
 * unsed in maintaing const function
 * Return: exits eith a given exit status (0)
 * if info.argv[0] != "exit"
 */

int shexit(info_t *info)
{
	int exitchecks;

	if (info->argv[1]) /* to an exit argument */
	{
		exitchecks = _erratois(info->argv[1]);
		if (exitchecks == -1)
		{
			info->status = 2;
			gives_error(info, "Illegal num: ");
			puts(info->argv[1]);
			putchar('\n');
			return (1);
		}
		info->err_num = _erratois(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * cd_change - changes the current dir of the process
 * @info: stru containing arguments used in function
 * Return: Always 0
 */
int cd_change(info_t *info)
{
	char *a, *di, buffer[1024];
	int dirch;

	a = getcwd(buffer, 1024);

	if (!a)
		puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		di = getenv("HOME");
		if (!di)
			dirch = /* ? */
				chdir((di = getenv("PWD")) ? di : "/");
		else
			dirch = chdir(di);
	}
	else if (strcmp(info->argv[1], "-") == 0)
	{
		if (!getenv("OLDPWD"))
		{
			puts(a);
			putchar('\n');
			return (1);
		}
		puts(getenv("OLDPWD"));
		putchar('\n');
		dirch = /* ? */
			chdir((di = getenv("OLDPWD")) ? di : "/");
	}
	else
		dirch = chdir(info->argv[1]);
	if (dirch == -1)
	{
		gives_error(info, "couldn't cd to ");
		printf("%s\n", info->argv[1]);
	}
	return (0);
}

/**
 * ushelp_ - changes the current dir of the process
 * @info: struct containing arguments used to maintain
 * function prototype
 * Return: Always 0
 */
int ushelp_(info_t *info)
{
	char **args_array;

	args_array = info->argv;
	puts("call help. Function not yet placed \n");
	if (0)
		puts(*args_array);
	return (0);
}

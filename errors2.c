#include "main.h"

/**
* _erratois - converts a string to an integer
* @w: the string to be converted
* Return: 0 if no numbers in string, converted number otherwise
* -1 on error
*/
int _erratois(char *w)
{
	int t = 0;
	unsigned long int result = 0;

	if (*w == '+')
		w++;
	for (t = 0;  w[t] != '\0'; t++)
	{
		if (w[t] >= '0' && w[t] <= '9')
		{
			result *= 10;
			result += (w[t] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
* gives_error - prints an error message
* @info: the parameter & return info struct
* @estr: string containing specified error type
* Return: 0 if no numbers in string, converted number otherwise
*/
void gives_error(info_t *info, char *estr)
{
	puts(info->fname);
	puts(": ");
	print_dec(info->line_count, STDERR_FILENO);
	puts(": ");
	puts(info->argv[0]);
	puts(": ");
	puts(estr);
}

/**
* print_dec - function prints a decimal (integer) number (base 10)
* @input: the input
* @fd: the filedescriptor to write to
* Return: number of characters printed
*/
int print_dec(int input, int fd)
{
	int (*__putchar)(char) = __putchar;
	int r, counts = 0;
	unsigned int _abs_, curr;

	if (fd == STDERR_FILENO)
		__putchar = __putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		counts++;
	}
	else
		_abs_ = input;
	curr = _abs_;
	for (r = 1000000000; r > 1; r /= 10)
	{
		if (_abs_ / r)
		{
			__putchar('0' + curr / r);
			counts++;
		}
		curr %= r;
	}
	__putchar('0' + curr);
	counts++;

	return (counts);
}

/**
* convert_num - converter function, a clone of itoa
* @num: number
* @base: base
* @flags: argument flags
* Return: string
*/
char *convert_num(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long m = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		m = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[m % base];
		m /= base;
	} while (m != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
* delete_comments - function replaces first instance of '#' with '\0'
* @buff: address of the string to modify
* Return: Always 0;
*/
void delete_comments(char *buff)
{
	int k;

	for (k = 0; buff[k] != '\0'; k++)
		if (buff[k] == '#' && (!k || buff[k - 1] == ' '))
		{
			buff[k] = '\0';
			break;
		}
}

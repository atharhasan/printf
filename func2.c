#include "main.h"

/**
 * print_pointer - function that can print the value of pointer
 * @lis: list of arguments
 * @buffer: buffer array to handel buffer
 * @flags: calculate active flags
 * @width: width
 * @precision: precision specification
 * @size: size specifier
 * Return: size of output
*/

int print_pointer(va_list lis, char buffer[], int flags, int width,
int precision, int size)
{
	char ex_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, len = 2, padd_start = 1;
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(lis, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "NULL", 4));
	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);
	num_addrs = (unsigned long)addrs;
	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		len++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		ex_c = '+', len++;
	else if (flags & F_SPACE)
		ex_c = ' ', len++;
	ind++;
	return (write_pointer(buffer, ind, len, width,
		flags, padd, ex_c, padd_start));
}

/**
 * print_non_printable - print ascii codes in hexa on non printable chars
 * @lis: list of arguments
 * @buffer: buffer array to handel buffer
 * @flags: calculate active flags
 * @width: width
 * @precision: precision specification
 * @size: size specifier
 * Return: size of output
*/

int print_non_printable(va_list lis, char buffer[], int flags, int width,
int precision, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(lis, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
		return (write(1, "(null)", 6));
	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buffer[i + offset] = srt[i];
		offset += append_hexa_code(str[i], buffer, i + offset);
		i++;
	}
	buffer[i + offset] = '\0';
	return (write(1, buffer, i + offset));
}

/**
 * print_reverse - print reverse string
 * @lis: list of arguments
 * @buffer: buffer array to handel buffer
 * @flags: calculate active flags
 * @width: width
 * @precision: precision specification
 * @size: size specifier
 * Return: size of output
*/

int print_reverse(va_list lis, char buffer[], int flags, int width,
int precision, int size)
{
	char *str;
	int i, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);
	str = va_arg(lis, char *);
	if (str == NULL)
	{
		UNUSED(precision);
		str = "(null)";
	}
	for (i = 0; str[i]; i++)
		;
	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}

/**
 * print_rot13 - print string in rot13
 * @lis: list of arguments
 * @buffer: buffer array to handel buffer
 * @flags: calculate active flags
 * @width: width
 * @precision: precision specification
 * @size: size specifier
 * Return: size of output
*/

int print_rot13(va_list lis, char buffer[], int flags, int width,
int precision, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(lis, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];

			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}

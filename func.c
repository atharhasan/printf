#include "main.h"

/**
 * print_char - function that can print char
 * @lis: list of arguments
 * @buffer: buffer array to handel buffer
 * @flags: calculate active flags
 * @width: width
 * @precision: precision specification
 * @size: size specifier
 * Return: size of output
*/

int print_char(va_list lis, char buffer[], int flags, int width,
int precision, int size)
{
	char c = va_arg(lis, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/**
 * print_string - function that can print string
 * @lis: list of arguments
 * @buffer: buffer array to handel buffer
 * @flags: calculate active flags
 * @width: width
 * @precision: precision specification
 * @size: size specifier
 * Return: size of output
*/

int print_string(va_list lis, char buffer[], int flags, int width,
int precision, int size)
{
	int len = 0, i;
	char *str = va_arg(lis, char*);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			srt = "      ";
	}
	while (str[len] != '\0')
		len++;
	if (precision >= 0 && precision < len)
		len = precision;
	if (width > len)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], len);
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (width);
		}
	}
	return (write(1, str, len));
}

/**
 * print_percent - function that can print percent sign
 * @lis: list of arguments
 * @buffer: buffer array to handel buffer
 * @flags: calculate active flags
 * @width: width
 * @precision: precision specification
 * @size: size specifier
 * Return: size of output
*/

int print_percent(va_list lis, char buffer[], int flags, int width,
int precision, int size)
{
	UNUSED(lis);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	return (write(1, "%%", 1));
}

/**
 * print_int - function that can print int
 * @lis: list of arguments
 * @buffer: buffer array to handel buffer
 * @flags: calculate active flags
 * @width: width
 * @precision: precision specification
 * @size: size specifier
 * Return: size of output
*/

int print_int(va_list lis, char buffer[], int flags, int width,
int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(lis, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}
	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}
	i++;
	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/**
 * print_binary - function that can print unsigned number
 * @lis: list of arguments
 * @buffer: buffer array to handel buffer
 * @flags: calculate active flags
 * @width: width
 * @precision: precision specification
 * @size: size specifier
 * Return: size of output
*/

int print_binary(va_list lis, char buffer[], int flags, int width,
int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	n = va_arg(lis, unsigned int);
	m = 2147483648;
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}

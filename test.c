#include <unistd.h>

typedef size_t (* convert_signed_int)(char *result, int n);
typedef size_t (* convert_unsigned_int)(char *result, unsigned int n);
typedef size_t (* convert_pointer)(char *result, void *p);



enum e_printf_flags
{
	LEFT_JUSTIFY = 1,			// -
	ZERO_PADDING = 2,			// 0
	DISPLAY_SIGN = 4,			// +
	SPACE_FOR_SIGN = 8,			// [ ](white space)
	ALT = 16					// #
};

enum e_supported_types
{
	// cspdiuxX
	CHARACTOR = 'c',
	STRING = 's',
	POINTER = 'p',
	DECIMAL = 'd',
	INTEGER = 'i',
	UNSIGNED_INTEGER = 'u',
	HEXDECIMAL_LOW = 'x',
	HEXDECIMAL_HIGH = 'X'
};

typedef struct s_print_info
{
	size_t			min_len;
	size_t			max_len;
	unsigned char	flag;
}	t_printf_info;

/*
s_print_info *parse_format_string(const char *format, ...)
{

}
*/

#include <stdarg.h>

unsigned char search_flagset(const char c)
{
	if (c == '-')
		return (LEFT_JUSTIFY);
	if (c == '0')
		return (ZERO_PADDING);
	if (c == '+')
		return (DISPLAY_SIGN);
	if (c == ' ')
		return (SPACE_FOR_SIGN);
	if (c == '#')
		return (ALT);
	return (0);
}

unsigned char process_flags(const char **format)
{
	unsigned char	flags;
	unsigned char	flag;

	flag = search_flagset(**format);
	while (flag)
	{
		flags |= flag;
		*format += 1;
		flag = search_flagset(**format);
	}
	return (flags);
}

int is_digit(int n)
{
	if ('0' <= n && n <= '9')
		return (1);
	return (0);
}

unsigned int process_width(const char **format)
{
	unsigned int width;

	width = 0;
	while (is_digit(**format))
	{
		width = width * 10 + (**format - '0');
		*format += 1;
	}
	return (width);
}

unsigned int process_precision(const char **format)
{
	if (**format == '.')
	{
		*format += 1;
		return (process_width(format));
	}
	return (0);
}

int in_typeset(const char c, const char *set)
{
	while(*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

int process_type(const char **format)
{
	while (**format != '\0' && !in_typeset(**format, "cspdiuxX"))
		*format += 1;
	return (**format);
}



int ft_printf (const char *format, ...)
{
	va_list			arg_pointer;
	t_printf_info	printf_info;
	void			*convert_func;
	int				type;

	while (*format != '\0')
	{
		if (*format == '%')
		{
			if (*(format + 1) == '%')
				write(1, format++, 1);
			else
			{
				printf_info.flag = process_flags(&format);
				printf_info.min_len = process_width(&format);
				printf_info.max_len = process_precision(&format);
				type = process_type(&format);
				if (type == DECIMAL || type == INTEGER)
				{
					with_flags();
				}
				else if (type == UNSIGNED_INTEGER || type == HEXDECIMAL_HIGH || type == HEXDECIMAL_LOW)
				{

				}
				else if (type == STRING)
				{

				}
				else if (type == POINTER)
				{

				}
				else if (type == CHARACTOR)
				{

				}
			}
		}
		format++;
	}
}

int main(void)
{
	return 0;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:55:35 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/20 20:57:10 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

static const t_get_argf g_get_argf_table[10] = \
{
	get_arg_as_pointer,
	get_arg_as_char,
	get_arg_as_int,
	get_arg_as_string,
	get_arg_as_uint,
	get_arg_as_uint,
	NULL,
	get_arg_as_int,
	get_arg_as_uint,
	get_percent_sign
};

static const t_arg_to_stringf g_arg_to_stringf_table[10] = \
{
	pointer_to_string,
	char_to_string,
	int_to_string,
	string_to_string,
	uhex_high_to_string,
	uint_to_string,
	NULL,
	int_to_string,
	uhex_low_to_string,
	percent_sign_to_string
};

void ft_putchar_repeat(char c, size_t r)
{
	while(r--)
		write(1, &c, 1);
}

typedef struct s_string_info
{
	char	left_sign;
	char	*prefix;
	char	*main_part;
	size_t	total_size;
}

#include <stdio.h>

/*
	print_left_sign()
	print_prefix()
	print_main()
*/

size_t print_arg_with_format(struct s_format_info *fi, va_list *va)
{
	union u_arg arg;
	int sign_space;
	char buf[30];
	char *p_buf;
	size_t len;

	p_buf = buf;
	g_get_argf_table[fi->type % 14](&arg, va);
	sign_space = ((fi->type == 'i' || fi->type == 'd') && (arg.i < 0));
	len = g_arg_to_stringf_table[fi->type % 14](&p_buf, &arg, fi);
	ft_putchar_repeat(int_selector(' ', '0', fi->flag & ZERO_PAD), (len < fi->min_len) * (fi->min_len - len) * ((fi->flag & RIGHT_ALIGN) == 0));
	sign_space = (fi->flag & POS_SIGN) || (fi->flag & EMPTY_SPACE) || sign_space;
	write(1, p_buf, len - sign_space);
	ft_putchar_repeat(' ', (len < fi->min_len) * (fi->min_len - len) * ((fi->flag & RIGHT_ALIGN) != 0));
	return (max(len, fi->min_len));
}

typedef ssize_t (*parserf)(const char *format, va_list *va);
static const parserf with_end_state_normal[2] = {__normal, __end};
static const parserf with_end_state_format[2] = {__format, __end};

ssize_t __normal(const char *format, va_list *va)
{
	ssize_t result;
	const char *word;
	size_t word_len;
	
	word = format;
	word_len = 0;
	while(*format && *format != '%')
	{
		word_len++;
		format++;
	}
	result = write(1, word, word_len);
	return (with_end_state_format[*format == '\0'](format + 1, va) + result);
}

ssize_t __format(const char *format, va_list *va)
{
	ssize_t result;
	struct s_format_info fi;

	format = parse_format(format, &fi);
	result = print_arg_with_format(&fi, va);
	return (with_end_state_normal[*format == '\0'](format + 1, va) + result);
}

ssize_t __end(const char *format, va_list *va)
{
	return (0);
}

size_t ft_printf(const char *format, ...)
{
	va_list va;
	ssize_t total_len;
	
	total_len = 0;
	va_start(va, format);
	total_len = __normal(format, &va);
	va_end(va);
	return total_len;
}
['', '','','']